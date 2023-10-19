#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 189
#define MAX_COLS 6

int main() {
    char buffer[1024];
    char *data[MAX_ROWS][MAX_COLS];
    int rows = 0;

    FILE *csv_file = fopen("flights.csv", "r");
    if (!csv_file) {
        perror("Failed to open the file");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), csv_file) && rows < MAX_ROWS) {
        int cols = 0;
        char *token = strtok(buffer, ",");
        
        while (token != NULL && cols < MAX_COLS) {
            data[rows] [cols] = strdup(token);
            token = strtok(NULL, ",");
            cols++;
        }
        
        rows++;
    }

    fclose(csv_file);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAX_COLS && data[i] [j] != NULL; j++) {
            printf("%s\t", data[i] [j]);
            free(data[i] [j]); 
        }
        printf("\n");
    }

    return 0;
}
