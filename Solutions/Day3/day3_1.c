#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Open input
    FILE* input = fopen("../../Data/day3.txt", "r");

    // Check if File is really open
    if(input == NULL){
        printf("File could not be openend!");
        exit(1);
    }

    // length of binary numbers
    int length = 12;

    int* ones = malloc(length * sizeof(int));
    char* binary = malloc(length);
    int numbers = 0;

    // Loop as long as there are binary numbers
    while(fscanf(input, "%s \n", binary) > 0){
        // add to ones to ones count
        for(int i = 0;i < length;i++){
            ones[i] += binary[i] - 48;
        }

        // count how many numbers there are
        numbers += 1;
    }

    // Calculate gamma and epsilon
    int gamma = 0;
    int epsilon = 0;
    int multiple_2 = 1;

    // Loop over every bit
    for(int i = length - 1;i >= 0;i--){
        // If the most commen bit is 1 add to gamme
        if(ones[i] > numbers - ones[i]){
            gamma += multiple_2;
        // else add to epsilon
        }else {
            epsilon += multiple_2;
        }

        multiple_2 *= 2;
    }

    // Print Result
    printf("Gamma: %d , Epsilon: %d \n", gamma, epsilon);
    printf("Result :%d \n", gamma * epsilon);

    fclose(input);
}