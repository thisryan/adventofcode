#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_length = 12;

// struct to represent one binary number
typedef struct {
    int active;
    char* bin;
} bnode;

int bin_to_dec(char*);
int deactive_bins(bnode*, int, int, int, int*, bnode**);

int main() {
    // Open File
    FILE* input = fopen("../../Data/day3.txt", "r");

    // Check if File is really open
    if(input == NULL){
        printf("File could not be openend!");
        exit(1);
    }

    // We manage bins like a ArrayList
    int length = 128;
    bnode* bins = malloc(length * sizeof(bnode));

    int numbers = 0;
    char* binary = malloc(bin_length+1);
    int* ones = malloc(bin_length * sizeof(int));

    // 48 is the ascii represnation of 0
    // so ascii 0 - 48 would be integer 0 and ascii 1 - 48 would be integer 1
    // Loop as long as we have input number
    while(fscanf(input, "%s \n", binary) > 0){
        // Every binary number is active in the beginning 
        bins[numbers].active = 1;

        // Put binary String in current binary number
        bins[numbers].bin = malloc(bin_length+1);
        strcpy(bins[numbers].bin, binary);
        numbers += 1;

        // Count how many ones are in number
        for(int i = 0;i < bin_length;i++){
            ones[i] += binary[i] - 48;
        }

        // if we have reached the end of the ArrayList expand it
        if(numbers == length){
            length *= 2;
            bins = realloc(bins, length * sizeof(bnode));
        }
    }

    free(binary);

    // Cut bins down to actual length
    length = numbers;
    bins = realloc(bins, length * sizeof(bnode));
    printf("length: %d \n", length);

    if(bins == NULL){
        printf("Realloc failed! \n");
        exit(1);
    }

    // Copy ones to second array
    int* ones_2 = malloc(bin_length * sizeof(int));
    for(int i = 0;i < bin_length;i++){
        ones_2[i] = ones[i];
    }

    int active = numbers;   
    int bit_pos = 0;
    int bit;
    bnode* result;

    do {
        // If there are more 1 current bit is 1
        bit = ones[bit_pos] >= (active - ones[bit_pos]);

        // deactive bins and chane ones
        active = deactive_bins(bins, length, bit, bit_pos, ones,&result);
        bit_pos++;
    }while(active > 1);

    // the Ox-rating is the decimal represantation of last active binary number
    int ox_rating = bin_to_dec(result->bin);

    // Reactivate every binary number
    for(int i = 0;i < length;i++){
        bins[i].active = 1;
    }
    
    // now do the same Loop as above but now use the opposite bit 
    // and use ones_2 because it is unaltered 
    active = numbers;   
    bit_pos = 0;
    do {
        // And now if there are less 1 the bit is 1
        bit = ones_2[bit_pos] < (active - ones_2[bit_pos]);
        active = deactive_bins(bins, length, bit, bit_pos, ones_2,&result);
        bit_pos++;
    }while(active > 1);

    // Co2-rating is decimal represantation of last active binary number
    int co2_rating = bin_to_dec(result->bin);

    // Print result
    printf("Ox-raiting: %d, co2-rating: %d \n", ox_rating, co2_rating);
    printf("life-support: %d \n", ox_rating * co2_rating);

    // Free data
    for(int i = 0;i < length;i++){
        free(bins[i].bin);
    }
    free(bins);
    free(ones);
    free(ones_2);
    fclose(input);
}

int deactive_bins(bnode* bins, int length, int bit, int bit_pos, int* ones, bnode** result) {
    int active = 0;
    int cur_bit;

    // Loop over every binary number
    for(int i = 0; i < length;i++){
        // if binary number is already inactive ignore it 
        if(!bins[i].active) continue;

        // get bit of current binary as bit_pos
        cur_bit = bins[i].bin[bit_pos] - 48;
        
        // If current bit is not the bit is should be dactivate binary number
        if(cur_bit != bit){
            // set inactive
            bins[i].active = 0;

            // Remove every counted one from ones
            for(int j = bit_pos;j < bin_length;j++){
                ones[j] -= bins[i].bin[j] - 48;
            }
        // else count ist as active
        }else {
            *result = bins + i;
            active += 1;
        }
    }

    // return how many are active
    return active;
}

// convert binary to decimal
int bin_to_dec(char* bin){
    int dec = 0;
    int multiple_2 = 1;
    // Loop in reverse so we start with lowest bit
    for(int i = strlen(bin)-1;i >= 0;i--){
        // multiply current bit with current multiple of 2
        dec += (bin[i] - 48) * multiple_2;
        multiple_2 *= 2;
    }

    return dec;
}