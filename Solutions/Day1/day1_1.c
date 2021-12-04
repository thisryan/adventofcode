#include <stdio.h>
#include <stdlib.h>

int main(){
    // Open File
    FILE* input = fopen("../../Data/day1.txt", "r");

    // Check if File is really open
    if(input == NULL){
        printf("Input could not be opened \n");
        exit(1);
    }

    int num[2];
    int difference = 0;

    // Loop as long as we find values
    fscanf(input, "%d \n", num);
    while(fscanf(input, "%d \n", num+1) > 0){
        // if num[1] is greater num[0] this checks gives 1
        difference += num[1] > num[0];

        num[0] = num[1];
    }

    // Print Result
    printf("Difference: %d \n", difference);
}