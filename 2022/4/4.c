#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct bounds {
    int left[2];
    int right[2];
};

struct bounds parseLine(char *line) {
    struct bounds result;
    size_t linelen = strlen(line);

    size_t side = 0; //0 (left) or 1 (right)
    size_t elf = 0; //0 (left) or 1 (right)
    //once we set a token to \0 we need to
    //jump back to the start of the string
    //pare the bound
    //then jump forward so we can parse the next string
    //again assuming valid inputs here.
    size_t seekoffset = 0;

    for (size_t i = 0; i < linelen; i++) {
        char current = line[i];

        if (current == '-' || current == ',') {
            line[i] = '\0';
            //pointer arithmetic to get the substring
            //https://beej.us/guide/bgc/html/split/pointers2.html#pointers2
            int bound = atoi(&line[i]-seekoffset);
            printf("elf: %zu, offset: %zu, bound: %zu, %d\n", elf, seekoffset, side, bound);
            seekoffset = 0;

            if (current == ',') {
                elf = 1;
                side = 0;
            }

            if (current == '-') {
                side = 1;
            }
            continue;
        }
        printf("%c\n", current);

        seekoffset += 1;
    }
    return result;
}

int main() {
   FILE* input = fopen("./input.txt", "r");
   char line[100];

   while(fgets(line, sizeof(line), input) != NULL) {
    parseLine(line);
   }
}
