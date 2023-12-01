#include <stdio.h>

#include <stdlib.h>

#include <string.h>

//#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array+

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
struct FITNESS_DATA {
  char date[11];
  char time[6];
  char steps[6];
};

struct FITNESS_DATA fitness_array[1024];

void tokeniseRecord(const char * input,
  const char * delimiter,
    char * date, char * time, char * steps) {
  // Create a copy of the input string as strtok modifies the string
  char * inputCopy = strdup(input);

  // Tokenize the copied string
  char * token = strtok(inputCopy, delimiter);
  if (token != NULL) {
    strcpy(date, token);
  }

  token = strtok(NULL, delimiter);
  if (token != NULL) {
    strcpy(time, token);
  }

  token = strtok(NULL, delimiter);
  if (token != NULL) {
    strcpy(steps, token);
  }

  // Free the duplicated string
  free(inputCopy);
}

char choice;

FILE * file;

char date[11];
char time[6];
char steps[20];

int action(int option) {
  switch (option) {
    case 'A':
    case 'a':
        ;
        char line[1024];
        char filename[1024];

        printf("Input filename: ");
        scanf(" %s", filename);

        int counter = 0;

        file = fopen(filename, "r");

        if (!file)
        return printf("Can't open file\n");
        else
        (
            printf("File successfully loaded.\n"));

        while (fgets(line, 1024, file)) {
        struct FITNESS_DATA record;

        tokeniseRecord(line, ",", record.date, record.time, record.steps);
        fitness_array[counter] = record;
        counter++;
        }

        fclose(file);

        break;
    case 'B':
    case 'b':
        printf("Number of records in file: %i\n", counter);
        break;

    case 'Q':
    case 'q':
        exit(1);

    default:
        printf("Invalid choice. Try again.\n");

    int lowest_steps;
    int i;
    int lowest_i;
    case 'c':
    case 'C':
        lowest_steps = 999999;
        
        for(i=0;i < counter;i++){
        if (atoi(fitness_array[i].steps) < lowest_steps ){
        lowest_steps = atoi(fitness_array[i].steps);
        lowest_i = i;

      } 
   }
      printf("The date and timeslot with the lowest steps are: %s,%s\n", fitness_array[lowest_i].date, fitness_array[lowest_i].time );
      break;

    int highest_steps;
    int highest_i;
    case 'D':
    case 'd':
        highest_steps = 0;

        for (i = 0; i < counter; i++) {
        if (atoi(fitness_array[i].steps) > highest_steps) {
        highest_steps = atoi(fitness_array[i].steps);
        highest_i = i;
    }
}      
        printf("The date and timeslot with the highest steps are: %s,%s\n", fitness_array[highest_i].date, fitness_array[highest_i].time );
        break;

    int total;
    float mean;
    case 'e':
    case 'E':

    total= 0;
    for (i=0 ; i < counter; i++){
      total = total + atoi(fitness_array[i].steps);
    }
    mean = (float)total/counter;
    printf("The mean step count is %.2f\n", mean);
    break;

    int longest_period = 0;
        int current_period = 0;
        int startPeriod;
        int endPeriod;
        case 'f':
        case 'F':
            startPeriod = 0;
            endPeriod = 0;
            longest_period = 0;
            current_period = 0;

            for (int i = 0; i < counter; i++) {
                int current_steps = atoi(fitness_array[i].steps);

                if (current_steps > 500) {
                    current_period++;

                    if (current_period == 1) {

                        startPeriod = i;
                    }
                } else {
                    current_period = 0;
                }

                if (current_period > longest_period) {
                    longest_period = current_period;
                    endPeriod = i;
                }
            }

            if (longest_period > 0) {
                printf("The longest period with steps over 500 starts at: %s, %s\n", fitness_array[startPeriod].date, fitness_array[startPeriod].time);
                printf("And ends at: %s, %s\n", fitness_array[endPeriod].date, fitness_array[endPeriod].time);
            } else {
                printf("No period with steps over 500 found.\n");
            }
            break;
    
    }
}

int main() {
  while (1 > 0) {

    printf("Menu Options:\n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");
    char option;

    printf("Enter Option: ");
    option = getchar();

    action(option);

    fflush(stdin);
    while ((option = getchar()) != '\n');
  }
}

   