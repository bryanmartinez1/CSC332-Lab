#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    int file_destination_1, file_destination_2;

    file_destination_1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);

    file_destination_2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU);

    if(file_destination_1 < 0) {
        printf("Error in Opening");
        return 0;
    }
    if(file_destination_2 < 0){
        printf("Error in Opening");
        return 0;
    }

    close(file_destination_1);
    close(file_destination_2);

    return 0;
}