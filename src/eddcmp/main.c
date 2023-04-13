#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 4096

void check_args(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage: %s <file1> <file2> \n", argv[0]);
        printf("Where <file1> and <file2> are the files to compare\n");
        exit(1);
    }
}

int main(int argc, char *argv[]){
    check_args(argc, argv);

    FILE *original = fopen(argv[1], "r");
    FILE *target = fopen(argv[2], "r");

    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line1, MAX_LINE_LENGTH, original) != NULL){
        line_number++;
        fgets(line2, MAX_LINE_LENGTH, target);
        if (strcmp(line1, line2) != 0){
            printf("Files are different at line: %d\n", line_number);
            return 1;
        }
    }

    return 0;
}