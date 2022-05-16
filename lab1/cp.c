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

int main (int argc, char* argv[]) {
    int returnval, fd;
    char* filepath = argv[1], content[fd];
    //Check if it exists
    if (returnval == 0) {
        printf ("\n %s exists\n", filepath);
        // Since File Exists We Now Check User's Read Permission
        // Check read access
        readPermission(filepath);
        //Create a New File w/Read and Write Permission
        int cd = creat("destination.txt", S_IRWXU);
        //File Created No Error
        if (cd >= 0) {
            printf("%s has been created\n", filepath);
            // filepath gets opended and read
            fd = open(filepath, R_OK);
            if(fd > 0) {
                printf("%s - open() successful\n", filepath);
                int rd = read(fd, content, sizeof(content));
    
                if(rd >= 0) {
                    printf("Read Successful\n\n");

                    //Where the file gets copied

                    int destFile  = write(cd, content, rd);


                }
                else {
                    printf("* read() failed with error %s\n", strerror(errno));
                }
            }
        }
        //Error in Making File
        else if (cd < -1) {
            printf("* creat() failed with error %s\n", strerror(errno));
        }
    }
    else {
        if (errno == ENOENT) {
            // Creates the file that previously did not exist
            //S_IRWXU gives users permission to read and write file
            int cd = creat("destination.txt", S_IRWXU);
            //File Created No Error
            if (cd >= 0) {
                printf("destination.txt has been created\n");
                // filepath gets opended and read
                fd = open(filepath, R_OK);
                if(fd > 0) {
                    printf("%s - open() successful\n", filepath);
                    int rd = read(fd, content, sizeof(content));
    
                    if(rd >= 0) {
                        printf("Read Successful\n\n");
                    //Where the file gets copied
                    int destFile  = write(cd, content, rd);
                    }
                    else {
                        printf("* read() failed with error %s\n", strerror(errno));
                    }
                }
            //Error in Making File
                else if (cd < -1) {
                    printf("* creat() failed with error %s\n", strerror(errno));
                }
            }
        }
        else if (errno == EACCES){
            printf ("%s is not accessible\n", filepath);
            return 0;
        }
    }
    
return 0;
}