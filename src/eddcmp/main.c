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

int compare_without_spaces(const char *s1, const char *s2){
    while (*s1 != '\0' && *s2 != '\0'){
        if (*s1 == ' ' || *s1 == '\t'){
            s1++;
            continue;
        }
        if (*s2 == ' ' || *s2 == '\t'){
            s2++;
            continue;
        }
        if (*s1 != *s2){
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
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
        if (compare_without_spaces(line1, line2) != 0){
            printf("Files are different at line: %d\n", line_number);
            return 1;
        }
    }

    return 0;
}