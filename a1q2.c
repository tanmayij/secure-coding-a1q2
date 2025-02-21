#include <stdlib.h>
#include <stdio.h>
#include <string.h> //needed for input validation function
#define BUFSIZE 256
    
// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Usage: %s <address of the filename>\n", argv[0]);
        return -1;
    }

    //CORRECTION #1: input validation- filter special characters out from the input
    if (strpbrk(argv[1], "&;|<>`$(){}")) { //string function
        fprintf(stderr, "Error: Invalid filename. Special characters are not allowed.\n");
        return -1;
    }
    char cmd[BUFSIZE]; 
    //CORRECTION #2: use snprintf instead of strcpy to perform bounds checking on the input.
    int input = snprintf(cmd, BUFSIZE, "wc -c < \"%s\"", argv[1]);

    //if there was a buffer overflow, print a message 
    if (input >= BUFSIZE) {
        fprintf(stderr, "Error: Filename is too long.\n");
        return -1;
    }

    // CORRECTION #3: check if file exists before executing system()
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");  
        return -1;
    }
    fclose(file);

    //system call
    system(cmd);

    //add a return 
    return 0;
}
