#include <stdio.h>
#include <stdlib.h>
/**
 *此处注意*daytabs[]和(*daytabs)[]的区别。后者用于函数声明中，表明函数参数类型为一个指向数组的指针。
 */
static char daytabs[2][13]={
        {0,31,28,31,30,31,30,31,31,30,31,30,31},
        {0,31,29,31,30,31,30,31,31,30,31,30,31}};
int day_of_year(int,int,int);
void month_day(int,int,int*,int*);

int main()
{
    int month,day;
    month_day(1993,255,&month,&day);
    printf("The 255th day of 1993 is:%d/%d\n",month,day);

    printf("The 1993/9/12 is:%d\n",day_of_year(1993,9,12));
    return 0;
}

int day_of_year(int year, int month, int day){
    int daytab=0;
    daytab = year%4==0 && year%100!=0 || year%400 ==0;
    for(int i=0;i <month;i++)
        day = day + *(*daytabs+(daytab*13)+i);
        /** 此处*(*daytabs+(daytab*13)+i) 和 *(*(daytabs+daytab)+i)是等价的。 */
    return day;
}

void month_day(int year, int days, int *pmonth,int *pday){
    int daytab=0,i;
    daytab = year%4==0 && year%100!=0 || year%400 ==0;
    for(i=0;days > *(*(daytabs+daytab)+i);i++)
        days = days - *(*(daytabs+daytab)+i);
    *pmonth = i;*pday = days;
}
