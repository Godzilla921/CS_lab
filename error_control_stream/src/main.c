# include "csapp.h"
void fork1();
void fork2();
void fork3();
void fork4();
void fork5();
void fork6();
void fork7();
void fork8();
int main(int argc, char **argv, char **envp){
    // show argumnets
    // printf("Command line arguments: %d\n", argc);
    // for(int i=0; argv[i]!=NULL; ++i){
    //     printf("    argv[%2d]: %s\n", i, argv[i]);
    // }
    // printf("\n");
    // for(int i=0; envp[i]!=NULL; i++){
    //     printf("    envp[%2d]: %s\n", i, envp[i]);
    // }
    fork8();
    exit(0);
}
void fork1(){
    pid_t pid;
    int x = 1;

    pid = Fork();
    if (pid == 0){
       printf("Child : x= %d\n",++x);
       exit(0);
    }
    printf("Parent : x = %d\n",--x);
    exit(0);
}
void fork2()
{
	Fork();
	Fork();
	printf("Hello\n");
	exit(0);
}
void fork3(){
    if(Fork()==0){
        printf("Terminating Child, PID = %d\n", getpid());
        exit(0);
    }else{
        printf("Running Parent, PID = %d\n", getpid());
        while (1)
            ; /* Infinite loop */
    }
}
void fork4(){
    if (Fork() == 0) {
        /* Child */
        printf("Running Child, PID = %d\n",
        getpid());
        while (1)
            ; /* Infinite loop */
    } else {
        printf("Terminating Parent, PID = %d\n",
        getpid());
        exit(0);
    }
}
void fork5() {
    int child_status;
    if (fork() == 0) {
        printf("HC: hello from child\n");
        exit(0);
    } else {
        printf("HP: hello from parent\n");
        wait(&child_status);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
}
void fork6(){
    int status;
    int N = 10;
    pid_t pid;

    for(int i = 0; i < N; ++i){
        if((pid=Fork())==0){
            exit(100+i);
        }
    }
    while ((pid=wait(&status))>0){
        if(WIFEXITED(status)){
            printf("chile %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
        }else{
            printf("child %d terminated abnormally\n", pid);
        }
    }

    if(errno != ECHILD){
        unix_error("waitpid error");
    }
    
}
void fork7(){
    int status;
    int N = 10;
    pid_t pid[N], ret_pid;

    for(int i = 0; i < N; ++i){
        if((pid[i] = Fork())==0){
            exit(100+i);
        }
    }
    int i=0;
    while ((ret_pid=waitpid(pid[i++], &status, 0))>0){
        if(WIFEXITED(status)){
            printf("chile %d terminated normally with exit status = %d\n", ret_pid, WEXITSTATUS(status));
        }else{
            printf("child %d terminated abnormally\n", ret_pid);
        }
    }

    if(errno != ECHILD){
        unix_error("waitpid error");
    }
}

void fork8(){
    int status;
    int N = 10;
    pid_t pid[N], ret_pid;

    for(int i = 0; i < N; ++i){
        if((pid[i] = Fork())==0){
            while ((1))  // Infinit loop
                ;
            
        }
    }
    for (int i = 0; i < N; i++){
        printf("Kill child process %d\n", pid[i]);
        Kill(pid[i], SIGINT);
    }
    
    int i=0;
    while ((ret_pid=waitpid(pid[i++], &status, 0))>0){
        if(WIFEXITED(status)){
            printf("chile %d terminated normally with exit status = %d\n", ret_pid, WEXITSTATUS(status));
        }else{
            printf("child %d terminated abnormally\n", ret_pid);
        }
    }

    if(errno != ECHILD){
        unix_error("waitpid error");
    }
}