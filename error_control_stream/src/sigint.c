# include "csapp.h"

void sigint_handler(int sig){
    printf("Caught SIGINT!\n");
    exit(0);
}

int main(){
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        unix_error("signal error");
    }
    Pause();        // Wait for the receipt of a signal
    exit(0);
}