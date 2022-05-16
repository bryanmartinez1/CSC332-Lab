#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main () {
    int source_file = open("source.txt", O_RDONLY); 
    int destination1 = open("destination1.txt", O_WRONLY, S_IRWXU); 
    int destination2 = open("destination2.txt", O_WRONLY, S_IRWXU);
    
// Error In Opening Files
    if (source_file < 0) {
        printf("Error in Opening source.txt");
        return 0 ;
    }
    if (destination1 < 0) {
        printf("Error in Opening destination1.txt");
        return 0 ;
    }
    if (destination2 < 0) {
        printf("Error in Opening destination2.txt");
        return 0 ;
    }

// All Openings were Successful

    char buf100[100];
    char buf50[50];

    // 100 is for buf 100 and 50 is buf50
    int at_buf100_or_buf50 = 100;

    int read100;
    int read50;

    do {
        while (at_buf100_or_buf50 == 100 && (read100 = read(source_file, buf100, 100))) {
            for(int i = 0; i < read100; i++) {
                char characterHolder[1];

                characterHolder[0] = buf100[i];

                if (characterHolder[0] == '1') {
                    write(destination1, "L", 1);
                }
                else {
                    write(destination1, characterHolder, 1);
                }

            }
            //To finish While Statement
            at_buf100_or_buf50 = 50;
        }
        while (at_buf100_or_buf50 == 50 && (read50 = read(source_file, buf50, 50))) {
            for(int i = 0; i < read50; i++) {
                char characterHolder[1];

                characterHolder[0] = buf50[i];

                if (characterHolder[0] == '3') {
                    write(destination2, "E", 1);
                }
                else {
                    write(destination2, characterHolder, 1);
                }

            }
            //To finish While Statement
            at_buf100_or_buf50 = 100;
        }
    } while(read100 && read50);
    
    close(source_file);
    close(destination1);
    close(destination2);
    return 0;
}