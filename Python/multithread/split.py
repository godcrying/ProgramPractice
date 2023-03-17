import math
def split(n,m):
    L = []
    t = math.ceil(n/m)
    L.append((0,t))
    tmp = 0
    while m > 1:
        m-=1
        n-=t
        t = math.ceil(n/m)
        L.append((L[tmp][1]+1,L[tmp][1]+t))
        tmp+=1
    return L
