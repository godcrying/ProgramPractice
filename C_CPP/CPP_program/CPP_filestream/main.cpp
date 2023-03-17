#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char str[20]="How are you?";
    int i=40;

    ofstream out;
    out.open("test.txt",ios::out);
    if(out){
        out<<str<<'\0'<<i;
        out.close();
    }

    ifstream in;
    in.open("test.txt",ios::in);
    if(in){
        in.getline(str,20,'\0');
        in>>i;

         cout << str << endl;
         cout << i << endl;
         in.close();
    }

    return 0;
}
