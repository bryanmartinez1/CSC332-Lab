#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"


int main()
{
    int x = 0;
    do {

        printf("Hello World\n");

        x+=1;
    } while (x != 10);


    return 0;
}