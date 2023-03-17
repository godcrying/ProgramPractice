PNAME=fsm
IDIR=./include
CC=gcc
CFLAGS=-I$(IDIR)

BDIR=./bin
SDIR=./src
ODIR=./obj
LDIR=./lib

#若用到math.h的话，需要用-lm
#编程时并不是include头文件就可以了，编译时还需要加-l选项
#常用的libc库已经被gcc默认添加了，所以不需要-l选项
LIBS=

_DEPS = FSM.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = FSM.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
	
$(ODIR)/%.o:$(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(PNAME):$(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY:clean

clean:
	-rm $(BDIR)/* $(ODIR)/*.o 
