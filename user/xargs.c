#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char*argv[])
{
    int childargc=0;
    char *childargv[MAXARG];
    for(int i=1;i<argc;i++)
    {
        childargv[childargc]=argv[i];
        childargc++;
    }

    char buf[512];
    char *head=buf;
    char *p=buf;
    //这里感觉还是有点问题，如果输入的结尾不是\n，应该会出错
    while(read(0,p,1))
    {
        if(*p==' ')
        {
            *p=0;
            childargv[childargc]=head;//发现空格分割符，加入参数列表
            childargc++;
            p++;
            head=p;
        }
        else if(*p=='\n')
        {
            *p=0;
            //printf("%d---------------\n",' '==0);/ 这里发现‘ ’！=0，找了好久的bug
            childargv[childargc]=head;
            childargc++;
            childargv[childargc]=0;//参数结束
            if(fork()==0)
            {
                exec(argv[1],childargv);
            }
            else
            {
                wait(0);
                head=buf;//清空缓冲区buf
                p=buf;
                childargc=argc-1;//重置参数个数
            }
        }
        else
        {
            p++;
        }

    }
    exit(0);
}