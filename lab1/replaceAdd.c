#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void readPermission(char* filepath) {
    int read_file = access(filepath, R_OK);
    //User does HAVE Read Permission
    if(read_file == 0) {
        printf("%s - Permission to Read\n", filepath);
    }
    //User Does NOT Have Read Permission
    else if (errno == EACCES){
        printf("* Do NOT Have Read Permission %s\n", strerror(errno));
    }
}

void writePermission (char* filepath) {
    int write_file = access(filepath, W_OK);
    //User does HAVE Write Permission
    if(write_file >= 0) {
        printf("%s - Permission to Write\n", filepath);
    }
    //User Does NOT Have Write Permission
    else if (errno == EACCES){
        printf("* Do NOT Have Write Permission for %s\n", strerror(errno));
    }
}

int main (int argc, char* argv[]) {
    int fd, returnval;
    char* filepath = argv[1], content[fd];
    char buffer[10000];
    int reads = 10000;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0) {
        printf ("\n %s exists\n", filepath);
        // Since File Exists We Now Check User's Read Permission
        // Check read access
        readPermission(filepath);
        // Since File Exists We Now Check User's Write Permission
        // Check write access
        writePermission(filepath);
        //Creates Destination File
            int cd = creat("destination.txt", S_IRWXU);
            if(cd >= 0 ) {
                printf("destination.txt created\n");
            }
            else {
                printf("* read() failed with error %s\n", strerror(errno));
                return 0;
            }
        //Opens Original File
        int fd = open(filepath, O_RDONLY);
        if(fd > 0) {
            printf("%s - open() successful\n", filepath);

            // Reads File
            int rd = read(fd, buffer, 100000);
            int destFilOpen = open("destination.txt", O_RDWR);
            //Changes the first 100 characters of the file in where if it is a 1 changes it into an L
            for (int i = 0; i < 100; i++) {
                if(buffer[i] == '1') {
                    buffer[i] = 'L';
                }
            }
            //Saves Updated File to newly created destination file
            int destFile  = write(cd, buffer, rd);
            destFile = write(cd, "XYZ", 3);

            if (destFile >= 0) {
                printf("destination.txt file updated\n");
            }
            else {
                printf("Updated destination.txt file with error %s\n", strerror(errno));
            }

            int closed = close(fd);
            if(closed >= 0) {
                printf("\n%s - close() Successful\n", filepath);
            }
            else {
                printf("* close() failed with error %s\n", strerror(errno));
            } 
               
        }
        else if(fd < 0) {
            printf("* open() failed with error %s\n", strerror(errno));
            return 0;
        }
    }

    else {
        if (errno == ENOENT) {
            printf("%s does not exist\n", filepath);
            return 0;
        }
        else if (errno == EACCES){
            printf ("%s is not accessible\n", filepath);
            return 0;
        }
    }
return 0;
}