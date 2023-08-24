#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void fun(int pipe_out)
{
    
    int first;
    int num;
    if(read(pipe_out,&first,sizeof(int))!=0)printf("prime %d\n",first);
    else 
    {
        close(pipe_out);
        exit(0);
    }

    int p[2];
    pipe(p);
     //int num;
    while(read(pipe_out,&num,sizeof(int))!=0)
    {
        if(num%first!=0)write(p[1],&num,sizeof(int));
    }
    close(pipe_out);
    close(p[1]);
    if(fork()==0)
    {
        fun(p[0]);
    }
    else
    {
        wait(0);
    }
    exit(0);
}

int main(int argc, char*argv[])
{
    int nums[34];
    int p[2];
    pipe(p);
    for(int i=2;i<=35;i++)
    {
        nums[i-2]=i;
        if(write(p[1],nums+i-2,sizeof(int))<sizeof(int))exit(1);
    }
    close(p[1]);
    fun(p[0]);
    exit(0);
}