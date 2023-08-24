#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char*argv[])
{
    if(argc!=2)
    {
        printf("flase arg\n");
        exit(0);
    }
    int nticks=atoi(argv[1]);
    if(sleep(nticks)<0)exit(1);
    else exit(0);

}