#include <stdio.h>

int main () {
    int pid, pipefd[2];
    FILE *fp;

    //Child Process Made
    pid = fork();
    //Pipe made to read and write
    pipe(pipefd);
//if Fork Fails
    if(pid == -1) {
        printf("Fork Failed");
        return 0 ;
    }
//If Fork Succeeds
    if(pid == 0) {
    }

    return 0;
}