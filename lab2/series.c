#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
// Child 1 is the ODD series
// Child 2 is the even series

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2]; 
    int sumSeries1 = 0, sumSeries2 = 0, sumSeries3 = 0;
    int s1, s2;
    int sizeSeries1, sizeSeries2;
    if(argc < 2) {
        printf("Value was not given\n");
        return 0;
    }
// Turns value that was inputted by user from string to int
    int sizeSeries3 = atoi(argv[1]);

// Child One for Series 1
    s1 = fork();
    if(s1 < 0) {
        printf("Child 1 Failed\n");
        return 0;
    }

// Child Two for Series 2
    s2 = fork();
    if(s2 < 0) {
        printf("Child 2 Failed\n");
        return 0;
    }

// Parent (Series 3)
    if(s1 > 0 && s2 > 0) {
        printf("For Series 3 or the parent Series:\n");
        for (int i = 0; i < sizeSeries3; i++)
        {
            if(i == 0) {
                printf("%i",i+1);
                sumSeries3 = sumSeries3 + i + 1;
            }
            else {
                printf(" + %i", i+1);
                sumSeries3 = sumSeries3 + i + 1;
            }
        }
        printf(" = %i\n", sumSeries3);
        
        while(wait(NULL) > 0);
    }
// Child 1 or Series 1
    else if(s1 == 0 && s2 > 0) {
        while(wait(NULL) > 0);
        printf("For Series 1 or Child 1 Series:\n");
        for (int i = 0; i < sizeSeries3; i++)
        {
            if(i % 2 == 0) {
                if(i == 0) {
                printf("%i",i+1);
                sumSeries1 = sumSeries1 + i + 1;
                }
                else {
                    printf(" + %i", i+1);
                    sumSeries1 = sumSeries1 + i + 1;
                }
            }
            else continue;
        }
        printf(" = %i\n", sumSeries1);
    }
// Child 2
    else if(s1 > 0 && s2 == 0) {
        while(wait(NULL) > 0);
        printf("For Series 2 or Child 2 Series:\n");
        for (int i = 0; i < sizeSeries3; i++)
        {
            if(i % 2 != 0) {
                if(i == 1) {
                printf("%i",i+1);
                sumSeries2 = sumSeries2 + i + 1;
                }
                else {
                    printf(" + %i", i+1);
                    sumSeries2 = sumSeries2 + i + 1;
                }
            }
            else continue;
        }
        printf(" = %i\n", sumSeries2);
    }
    printf("\n");

    return 0;
}