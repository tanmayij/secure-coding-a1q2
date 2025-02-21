#include <stdio.h>
#include <stdlib.h>

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    //Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <address of the filename>\n", argv[0]);
        return -1;
    }

    //open the file in binary mode
    FILE *file = fopen(argv[1], "rb"); 
    if (file == NULL) {
        perror("Error opening file"); //print an error if file path is incorrect
        return -1;
    }

    //use fseek() to seek to end of file
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking file");
        fclose(file);
        return -1;
    }

    //get file size
    long file_size = ftell(file);
    if (file_size == -1) {
        perror("Error getting file size");
        fclose(file);
        return -1;
    }

    fclose(file);

    //print the final file_size. since this is not an input, we are not concerned about format string vulnerabilities in this case.
    printf("%ld\n", file_size);
    //add return
    return 0;
}
