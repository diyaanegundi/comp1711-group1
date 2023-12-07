#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            } else {
                *steps = -1; 
            }
        } else {
            strcpy(time, "00:00"); 
            *steps = -1;
        }
    } else {
        strcpy(date, "0000-00-00"); 
        strcpy(time, "00:00");
        *steps = -1;
    }
}

int compareSteps(const void *a, const void *b) {
    return ((FitnessData*)b)->steps - ((FitnessData*)a)->steps;
}

int main() {
    char filename[1024];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error: Could not find or open the file.\n");
        return 1;
    }

    int counter = 0;
    FitnessData fitness_array[1024];

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char date[11], time[6];
        int steps;

        tokeniseRecord(line, ',', date, time, &steps);

        if (steps == -1) {
            printf("Skipping invalid line: %s", line);
            continue;
        }

        strcpy(fitness_array[counter].date, date);
        strcpy(fitness_array[counter].time, time);
        fitness_array[counter].steps = steps;
        counter++;
    }

    fclose(file);

    qsort(fitness_array, counter, sizeof(FitnessData), compareSteps);

    char newFilename[1028];
    snprintf(newFilename, sizeof(newFilename), "%s.tsv", filename);

    FILE *newFile = fopen(newFilename, "w");

    if (!newFile) {
        printf("Error: Could not create or open the new file.\n");
        return 1;
    }

    for (int i = 0; i < counter; i++) {
        fprintf(newFile, "%s\t%s\t%d\n", fitness_array[i].date, fitness_array[i].time, fitness_array[i].steps);
    }

    fclose(newFile);

    printf("File successfully sorted and written to %s\n", newFilename);

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct {
//     char date[11];
//     char time[6];
//     int steps;
// } FitnessData;

// void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
//     char *ptr = strtok(record, &delimiter);
//     if (ptr != NULL) {
//         strcpy(date, ptr);
//         ptr = strtok(NULL, &delimiter);
//         if (ptr != NULL) {
//             strcpy(time, ptr);
//             ptr = strtok(NULL, &delimiter);
//             if (ptr != NULL) {
//                 *steps = atoi(ptr);
//             }
//         }
//     }
// }

// int compareSteps(const void *a, const void *b) {
//     return ((FitnessData*)b)->steps - ((FitnessData*)a)->steps;
// }

// int main() {
//     char filename[1024];
//     printf("Enter filename: ");
//     scanf("%s", filename);

//     FILE *file = fopen(filename, "r");

//     if (!file) {
//         printf("Error: Could not find or open the file.\n");
//         return 1;
//     }

//     int counter = 0;
//     FitnessData fitness_array[1024];

//     char line[1024];
//     while (fgets(line, sizeof(line), file)) {
//         tokeniseRecord(line, ',', fitness_array[counter].date, fitness_array[counter].time, &fitness_array[counter].steps);
//         counter++;
//     }

//     fclose(file);

//     qsort(fitness_array, counter, sizeof(FitnessData), compareSteps);

//     char newFilename[1028];
//     snprintf(newFilename, sizeof(newFilename), "%s.tsv", filename);

//     FILE *newFile = fopen(newFilename, "w");

//     if (!newFile) {
//         printf("Error: Could not create or open the new file.\n");
//         return 1;
//     }

//     for (int i = 0; i < counter; i++) {
//         fprintf(newFile, "%s\t%s\t%d\n", fitness_array[i].date, fitness_array[i].time, fitness_array[i].steps);
//     }

//     fclose(newFile);

//     printf("File successfully sorted and written to %s\n", newFilename);

//     return 0;
// }
