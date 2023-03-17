#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define true 1
#define false 0
#define OVERFLOW -2

typedef int status;

//字符串结构
typedef struct {
    char *elem;
    int length;
}String;

//模式结构
typedef struct {
    char *mode;
    int *next;
    int length;
}Strmode;

/*
*字符串结构操作
*/
//按指定字符串初始化字符串
status strAssign(String *S,char *s)
{
    int i;
    for(i=0;*(s+i) != '\0';i++);

    char *e = (char*)malloc((i+1)*sizeof(char));
    if(!e) exit(OVERFLOW);

    S->elem = e;
    S->length = i;

    while((*e++=*s++));//此处已经包含'\0'
    return OK;
}

//获取字符串长度
int strLength(String S)
{
    return S.length;
}

//对比字符串
int strCompare(String S1,String S2)
{
    char *s1=S1.elem;
    char *s2=S2.elem;

    //跳过相等部分
    while(*s1!='\0' && *s2!='\0' && *s1 == *s2){s1++;s2++;}

    return *s1-*s2;//因为此处不能受到运算符的副作用的影响，自增运算符不能写在while括号内。
}

//返回S1和S2连接之后的字符串
status strContact(String *T,String S1,String S2)
{
    int s1_len = S1.length;
    int s2_len = S2.length;
    char *s1=S1.elem;
    char *s2=S2.elem;

    char *t = (char*)malloc((s1_len+s2_len+1)*sizeof(char));
    if(!t) exit(OVERFLOW);

    T->elem = t;

    while(*s1 !='\0' && (*t++=*s1++));//括号不会影响逻辑运算符的判断顺序。
    while((*t++=*s2++));

    T->length = s1_len+s2_len;


    return OK;
}

//返回串S第pos位置起之后长度为len的子串
status strSub(String *Sb,String S,int pos,int len)
{
    int slen = S.length;
    if(slen-pos+1 < len || pos > slen || pos < 1) exit(OVERFLOW);

    char *subelem = (char *)malloc((len+1)*sizeof(char));
    if(!subelem) exit(OVERFLOW);

    Sb->elem = subelem;
    Sb->length = len;

    /*char *p = S.elem+pos-1;
    while(len--)
    {
        *subelem++=*p++;
    }*/
    //用for循环比较简洁，但是不容易理解。
    for(char *p = S.elem+pos-1;len--;*subelem++=*p++);
    *subelem='\0';

    return OK;
}

// 模式匹配，查找是否包含字串。
// 这里的pos是从0开始的。
int strIndex(String S,Strmode M,int pos)
{
    char *s=S.elem+pos;
    char *m=M.mode;
    int *n=M.next;
    int i=0,j=0;

    //此处如果使用m[i]!='\0'和s[j]!='\0'，会出现问题。因为可能会出现i=-1,m[-1]是非法的。
    while(j<S.length&& i<M.length)
    {
        if(i==-1 || s[j]==m[i]){
            j++;i++;
        }else{
            i=n[i];
        }
    }
    if(m[i]=='\0') return (j-M.length);

    return false;
}

/*
*模式串结构操作
*/

//初始化模式串
status strmodeCreate(Strmode *M,char *s)
{
    int i;
    for(i=0;*(s+i) != '\0';i++);
    char *m=(char*)malloc((i+1)*sizeof(char));
    if(!m) exit(OVERFLOW);

    M->mode = m;
    M->length = i;
    while((*m++=*s++));

    return OK;
}

//获取串的next值
status getNext(Strmode *M){
    int *n=(int *)malloc((M->length+1)*sizeof(int));
    if(!n) exit(OVERFLOW);
    M->next = n;
    //如果使用M.next，则会出现没有赋值的情况。

    /*该函数使用的是模式串的指针。
     *函数内部都是局部变量，如果传入的M是模式串实例而不是指针的话，
     *因为形参M和实参M不是同一个实例,使用M.next=n是无效的。
     */
    char *m=M->mode;
    int j=0,k=-1;
    n[j]=k;
    while(j<M->length-1)
    {
        if(k==-1 || m[j]==m[k]){
            j++;k++;
            n[j]=k;
        }else{
            k=n[k];
        }
    }

    return OK;
}





int main()
{
    String S,S1,S2,T,subStr;
    if(strAssign(&S,"Hello,world"))
        printf("S is %s\n",S.elem);
    strSub(&subStr,S,7,5);
    printf("subStr is %s\n",subStr.elem);

    if(strAssign(&S1,"Hello,Hello"))
        printf("S1 is %s\n",S1.elem);
    if(strAssign(&S2,"world,world"))
        printf("S2 is %s\n",S2.elem);

    int res;
    if((res=strCompare(S,S1))>0)
        printf("S is bigger than S1\n");
    else if(res<0)
        printf("S is smaller than S1\n");
    else
        printf("S is the same as S1\n");

    printf("-----------------\n");
    if(strContact(&T,S1,S2))
        printf("S1和S2连接之后的字符串为：%s\n",T.elem);

    printf("-------------------\n");

    String S3;
    Strmode M;
    if(strmodeCreate(&M,"abcaa"))
        printf("创建模式成功！！\n");
    if(getNext(&M))
        printf("计算NEXT值成功！！\n");

    for(int i=0;i<M.length;i++)
        printf("%d",(M.next)[i]);

    if(strAssign(&S3,"acbcabcbaabcaadcb"))
        printf("\n创建被匹配字符串成功！！\n");

    int pos=strIndex(S3,M,0);
    if(pos)
        printf("找到模式匹配的字符，位置:%d",pos);
    return 0;
}
