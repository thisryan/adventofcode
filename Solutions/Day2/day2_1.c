#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// struct for submarine position
typedef struct {
    int depth;
    int horizontal;
} sub;

int main() {    
    // Open input File
    FILE* input = fopen("../../Data/day2.txt", "r");

    // Check if File is open
    if(input == NULL){
        printf("Datei konnte nicht geöffnet werden!");
        exit(1);
    }

    sub submarine = {0, 0};
    int units;
    char command[50];

    // Loop as long as you read commands from file
    while(fscanf(input, "%s %d\n", command, &units) > 0){
        // Check which command it is and change value
        if(strcmp(command,"forward") == 0){
            submarine.horizontal += units;
        }else if(strcmp(command,"down") == 0){
            submarine.depth += units;
        }else if(strcmp(command,"up") == 0){
            submarine.depth -= units;
        }
    }

    // Print result
    printf("Depth: %d : Horizontal: %d \n", submarine.depth, submarine.horizontal);
    printf("Result: %d \n", submarine.horizontal * submarine.depth);
}