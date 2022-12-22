#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//we assume only good inputs
//takes in a char and returns its bitmask.
uint64_t mask(char theChar) {
    uint64_t shift = 0;
    if ((theChar >= 'a') && (theChar <= 'z')) {
        shift = (theChar - 'a');
    } else {
        shift = (theChar - 'A') + 26;
    }
    //this is critical, otherwise you get overflow.
    //https://stackoverflow.com/questions/26684351/bitwise-operations-on-unsigned-long-long-in-c
    return 1LLU << shift;
}

char unmask(uint64_t theMask) {
    //a shift multiplies by 2 (exponentation)
    //log2 gives the number of multiplications or shifts.
    int shifts = log2(theMask);
    if (shifts >= 0 && shifts <= 25) {
        return shifts + 'a';
    }
    return shifts + 'A' + 25;
}

int main() {
    FILE* input = fopen("./input.txt", "r");
    char buff[50];
    //read the full buffer each time.
    while(1) {
     //for each line
     uint64_t bitset = 0;
     if (fgets(buff, sizeof(buff), input) != NULL) {
        size_t len = strlen(buff) - 1; //-1 to drop the newline
        size_t i = 0;

        //set the bit mask
        while (i < len/2) {
            uint64_t theMask = mask(buff[i]);
            bitset = theMask | bitset;
            i += 1;
        }

        while (i < len) {
            uint64_t theMask = mask(buff[i]);
            if ((bitset & theMask) == theMask) {
                //https://stackoverflow.com/a/34459527/456809
                //bitset = bitset & ~theMask; //unset
                printf("common: %c %g\n", buff[i], log2(theMask));
            }
            i += 1;
        }
     } else {
        printf("errno: %d", errno);
        exit(errno);
     };
    }
}
