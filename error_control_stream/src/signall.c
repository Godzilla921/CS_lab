# include "csapp.h"

void handle1(int sig){
    int olderrno = errno;
    int pid;
    while((pid = wait(NULL))>0){
        Sio_puts("Handler reaped child.\n");
    }
    if(errno!= ECHILD){
        Sio_error("waitpid error");
    }
    
    Sleep(1);
    errno = olderrno;
}
int main(){

    char buf[MAXBUF];
    int n;
    if(signal(SIGCHLD, handle1) == SIG_ERR){
        unix_error("signal error");
    }

    for(int i=0; i<3; i++){
        if(Fork()==0){
            printf("Hello from child %d\n", getpid());
            exit(0);
        }
    }

    if((n = read(STDIN_FILENO, buf, sizeof(buf)))<0){
        unix_error("read error");
    }

    printf("Parent processging input\n");
    while(1);
    exit(0);
}