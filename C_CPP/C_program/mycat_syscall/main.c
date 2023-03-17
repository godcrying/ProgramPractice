#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void filecopy(int,int);

int main(int argc,char *argv[])
{
    int fp;
    if(argc == 1)
        filecopy(0,1);
    else
        while(--argc)
        {
            if((fp=open(*++argv,O_RDONLY)) == -1){
                printf("error:can't open file %s\n",*argv);
                exit(1);
            }else{
                filecopy(fp,1);
                close(fp);
            }
        }
    return 0;
}

/* copy from fp1 to fp2 */
void filecopy(int fp1,int fp2)
{
    char buff[BUFSIZ];
    int n;
    while((n=read(fp1,buff,BUFSIZ)) != 0)
        write(fp2,buff,n);
}
