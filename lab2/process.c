#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    int a = 10, b = 25, fr =0;;
            
    //PROCESS Q
    int fq = fork();
    //Child Successfully Forked
    if (fq == 0) {
        a += b;
        //Prints the values of a, b, and process_id
        printf("Process Q:\n    a = %i\n    b = %i\n    pid = %i\n", a, b, getpid());

    //PROCESS R
        fr = fork();

        if(fr != 0) {
            b += 20;
            printf("Process R:\n    a = %i\n    b = %i\n    pid = %i\n", a, b, getpid());
        }
        else {
            a = (a * b) + 30;
        printf("Process R:\n    a = %i\n    b = %i\n    pid = %i\n", a, b, getpid());
        }
    }
    else {
        b = a + b - 5;
        printf("Process Q:\n    a = %i\n    b = %i\n    pid = %i\n", a, b, getpid());
    }


    return 0;
}