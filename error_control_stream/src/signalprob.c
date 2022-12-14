# include "csapp.h"

volatile long counter = 2;

void handler1(int sig){
    sigset_t mask, prev_mask;

    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    Sio_putl(--counter);
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    _exit(0);
}

int main(){
    pid_t pid;
    sigset_t mask, prev_mask;
    printf("%ld", counter);
    fflush(stdout);

    signal(SIGUSR1, handler1);
    if((pid=Fork())==0){
        while (1)
        {
            /* code */
        }
        
    }
    Kill(pid, SIGUSR1);
    Wait(NULL);

    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    printf("%ld", ++counter);
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    exit(0);
}