# include "csapp.h"

int main()
{
    pid_t pid;

    if((pid=Fork())==0){
        Pause();  // Wait for a singal to arrive
        printf("control should never reach here!\n");
        exit(0);
    }

    Kill(pid, SIGKILL);
    exit(0);
}