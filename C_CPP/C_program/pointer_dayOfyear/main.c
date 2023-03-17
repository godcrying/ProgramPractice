#include <stdio.h>
#include <stdlib.h>

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
    if(year%4==0 && year%100!=0 || year%400 ==0)
        daytab = 1;
    /**
     * 此处可以写的更简洁一点：
     * daytab = year%4==0 && year%100!=0 || year%400 ==0;
     * 用if语句显得多此一举了。
     */
    for(int i=0;i <month;i++)
        day += daytabs[daytab][i];
    return day;
}

void month_day(int year, int days, int *pmonth,int *pday){
    int daytab=0,i;
    if(year%4==0 && year%100!=0 || year%400 ==0)
        daytab = 1;
    for(i=0;days > daytabs[daytab][i];i++)
        days -=daytabs[daytab][i];
    *pmonth = i;*pday = days;
}
