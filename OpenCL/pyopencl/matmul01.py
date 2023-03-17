# example provided by Eilif Muller

import pyopencl as cl
import numpy as np
import time

class Timer:    
    def __enter__(self):
        self.start = time.time()
        return self

    def __exit__(self, *args):
        self.end = time.time()
        self.interval = self.end - self.start

kernel= """
__kernel void blocked_matmul(const int N,
                      const __global float* A,
                      const __global float* B,
                      __global float* C) {
                      
    // Thread identifiers
    const int row = get_local_id(0); // Local row ID (max: TS)
    const int col = get_local_id(1); // Local col ID (max: TS)
    const int globalRow = TS*get_group_id(0) + row; // Row ID of C (0..M)
    const int globalCol = TS*get_group_id(1) + col; // Col ID of C (0..N)
 
    // Local memory to fit a tile of TS*TS elements of A and B
    __local float Asub[TS][TS];
    __local float Bsub[TS][TS];
 
    // Initialise the accumulation register
    float acc = 0.0f;
    
    // Loop over all tiles
    const int numTiles = N/TS;
    for (int t=0; t<numTiles; t++) {{
 
        // Load one tile of A and B into local memory
        const int tiledRow = TS*t + row;
        const int tiledCol = TS*t + col;
        Asub[row][col] = A[tiledCol + N * globalRow];
        Bsub[row][col] = B[globalCol + tiledRow * N];
 
        // Synchronise to make sure the tile is loaded
        barrier(CLK_LOCAL_MEM_FENCE);
 
        // Perform the computation for a single tile
        for (int k=0; k<TS; k++) {{
            acc += Asub[row][k] * Bsub[k][col];
        }}
 
        // Synchronise before loading the next tile
        barrier(CLK_LOCAL_MEM_FENCE);
    }}
 
    // Store the final result in C
    C[globalCol + globalRow * N] = acc;
}

"""


n = 1028
dtype='float32'
A = np.random.randn(n, n).astype(dtype)
B = np.random.randn(n, n).astype(dtype)

ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)
mf = cl.mem_flags
a_device = cl.Buffer(ctx, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=A)
b_device = cl.Buffer(ctx, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=B)
c_device = cl.Buffer(ctx, mf.WRITE_ONLY, A.nbytes)


ts = 4
prg = cl.Program(ctx, kernel).build(options=['-D', 'TS={0}'.format(ts)])
blocked_matmul = prg.blocked_matmul

with Timer() as t:
    event = blocked_matmul(queue, (n, n), (ts, ts), np.int32(n), a_device, b_device, c_device)
    event.wait()
print(t.interval)
