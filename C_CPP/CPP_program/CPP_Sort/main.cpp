#include <iostream>
#include "sqlist.h"
#include <stdio.h>
using namespace std;

int main()
{
    SqList<int,int> L;
    cout << L << endl;
   // printf("\n");
    L.QuickSort();
    cout << L <<endl;
    return 0;
}
