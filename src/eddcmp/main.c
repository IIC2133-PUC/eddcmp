#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 4096

void check_file_exists(char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        printf("File %s does not exist\n", filename);
        exit(1);
    }

    fclose(file);
}

void check_args(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage: %s <file1> <file2> \n", argv[0]);
        printf("Where <file1> and <file2> are the files to compare\n");
        exit(1);
    }
    check_file_exists(argv[1]);
    check_file_exists(argv[2]);
}

int compare_without_spaces(const char *s1, const char *s2){
    if ((*s1 == '\0' && *s2 != '\0' && *s2 != '\n') || (*s2 == '\0' && *s1 != '\0' && *s1 != '\n')){
        return 1;
    }

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

int compare_text_files(char* source_filename, char* target_filename){
    FILE *original = fopen(source_filename, "r");
    FILE *target = fopen(target_filename, "r");

    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line1, MAX_LINE_LENGTH, original) != NULL){
        line_number++;
        fgets(line2, MAX_LINE_LENGTH, target);
        if (compare_without_spaces(line1, line2) != 0){
            printf("Files are different at line: %d\n", line_number);
            exit(1);
        }
        memset(line1, 0, MAX_LINE_LENGTH);
        memset(line2, 0, MAX_LINE_LENGTH);
    }

    return 0;
}


int compare_binary_files(char* source_filename, char* target_filename){
    FILE *original = fopen(source_filename, "r");
    FILE *target = fopen(target_filename, "r");

    char byte1;
    char byte2;
    int byte_number = 0;

    while (fread(&byte1, sizeof(char), 1, original) != 0){
        byte_number++;
        fread(&byte2, sizeof(char), 1, target);
        if (byte1 != byte2){
            printf("Files are different at byte: %d\n", byte_number);
            exit(1);
        }
    }

    return 0;
}

int compare_files(char* source, char* target){
    char *source_extension = strrchr(source, '.');

    if (strcmp(source_extension, ".png") == 0 || strcmp(source_extension, ".bin") == 0){
        compare_binary_files(source, target);
    } else {
        compare_text_files(source, target);
    }
    return 0;
}


int main(int argc, char *argv[]){
    check_args(argc, argv);

    compare_files(argv[1], argv[2]);
    return 0;
}