#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Struct for submarine
typedef struct {
    int depth;
    int horizontal;
    int aim;
} sub;

int main() {
    // Open File
    FILE* input = fopen("../../Data/day2.txt", "r");

    // Check if File ist really open
    if(input == NULL){
        printf("Datei konnte nicht geöffnet werden!");
        exit(1);
    }

    sub submarine = {0, 0};
    int units;
    char command[50];

    // Loop as long as there are commands
    while(fscanf(input, "%s %d\n", command, &units) > 0){
        // Check command and change value
        if(strcmp(command,"forward") == 0){
            submarine.horizontal += units;
            submarine.depth += submarine.aim * units;
        }else if(strcmp(command,"down") == 0){
            submarine.aim += units;
        }else if(strcmp(command,"up") == 0){
            submarine.aim -= units;
        }
    }

    // Print result
    printf("Depth: %d : Horizontal: %d \n", submarine.depth, submarine.horizontal);
    printf("Result: %d \n", submarine.horizontal * submarine.depth);
}