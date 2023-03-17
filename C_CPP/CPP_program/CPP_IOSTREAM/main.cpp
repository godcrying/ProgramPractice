#include <iostream>

using namespace std;

int main()
{
    int flag=ios::scientific;
    for(int i=0x8000;i;i=i>>1)
    {
        if(flag&i)
            cout << 1;
        else
            cout << 0;
    }
    cout<<endl;

    int i=100;
    //课本上的习题此处没有加ios::basefield参数，导致输出结果全是100。
    cout.setf(ios::hex,ios::basefield);
    cout <<i<< "\t";
    cout <<i<< "\t";
    cout.setf(ios::dec,ios::basefield);
    cout <<i<< endl;
}
