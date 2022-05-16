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
    char* filepath = argv[1];
    int returnval;

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
    }
    else {
        if (errno == ENOENT) {
            // Creates the file that previously did not exist
            //S_IRWXU gives users permission to read and write file
            int cd = creat(filepath, S_IRWXU);
            if (cd >= 0) {
                printf("%s has been created\n", filepath);
                //Checks The Read and Write Permission
                readPermission(filepath);
                writePermission(filepath);
            }
            else if (cd == -1) {
                printf("* creat() failed with error %s\n", strerror(errno));
            }
        }
        else if (errno == EACCES){
            printf ("%s is not accessible\n", filepath);
            return 0;
        }
    }

// Open file and if file doesnt Exists, it creates it
    
    int fd = open(filepath, O_RDONLY);
    if(fd > 0) {
        printf("%s - open() successful\n", filepath);
    }
    else if(fd < 0) {
        printf("* open() failed with error %s\n", strerror(errno));
    }
    int closed = close(fd);
    if(closed >= 0) {
        printf("\n%s - close() Successful\n", filepath);
    }
    else {
        printf("* close() failed with error %s\n", strerror(errno));
    }   
return 0;
}