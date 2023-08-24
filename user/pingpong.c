#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc ,char*argv[])
{
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);

    char buffer[]={'a'};

    if(fork()==0)
    {
        close(p1[0]);
        close(p2[1]);

        

        if(read(p2[0],buffer,1)<1)exit(1);
        close(p2[0]);
        printf("%d: received ping\n",getpid());
        if(write(p1[1],buffer,1)<1)exit(1);

        close(p1[1]);
        
        exit(0);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        if(write(p2[1],buffer,1)<1)exit(1);

        close(p2[1]);

        if(read(p1[0],buffer,1)<1)exit(1);
        close(p1[0]);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}