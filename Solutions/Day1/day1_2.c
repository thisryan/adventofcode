#include <stdio.h>
#include <stdlib.h>

int main(){
    // Open file
    FILE* input = fopen("../../Data/day1.txt", "r");

    // Check if File is really open
    if(input == NULL){
        printf("Input could not be opened \n");
        exit(1);
    }

    // Sliding window
    int num[3];
    int difference = 0;

    // Read first 3 Values and calculate first sum
    fscanf(input, "%d \n", num);
    fscanf(input, "%d \n", num+1);
    fscanf(input, "%d \n", num+2);
    int prev_sum = num[0] + num[1] + num[2];

    // sum is now only num[1] + num[2]
    int sum = prev_sum - num[0];
    num[0] = num[1];
    num[1] = num[2];

    // Read values until we dont find anymore
    while(fscanf(input, "%d \n", num+2) > 0){
        // Add new number to current sum
        sum += num[2];

        // If sum is greater than prev_sum checks returns 1
        difference += sum > prev_sum;

        // current sum is now prev_sum
        prev_sum = sum;

        // subtract oldest value from sum
        sum -= num[0];
        num[0] = num[1];
        num[1] = num[2];
    }

    // Print Result
    printf("Difference: %d \n", difference);
    fclose(input);
}