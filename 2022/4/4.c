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
        int bound;
        //when it's the last thing to parse just parse the string.
        if (elf == 1 && side == 1) {
            printf("%c\n", line[i]);
            bound = atoi(&line[i]);
            result.right[1] = bound;
            break;
        }

        if (current == '-' || current == ',') {
                line[i] = '\0';
                //pointer arithmetic to get the substring
                //https://beej.us/guide/bgc/html/split/pointers2.html#pointers2
                bound = atoi(&line[i]-seekoffset);
                seekoffset = 0;

            if (elf == 0) {
                result.left[side] = bound;
            } else {
                result.right[side] = bound;
            }

            if (current == ',') {
                elf = 1;
                side = 0;
            }

            if (current == '-') {
                side = 1;
            }
            continue;
        }

        seekoffset += 1;
    }
    return result;
}

int main() {
   FILE* input = fopen("./input.txt", "r");
   char line[100];
   int count = 0;
   while(fgets(line, sizeof(line), input) != NULL) {
    struct bounds lineBounds = parseLine(line);
    printf("elf0: (%d,%d), elf1: (%d,%d)\n",
     lineBounds.left[0],lineBounds.left[1],
     lineBounds.right[0], lineBounds.right[1]);
    if (
        (lineBounds.left[0] >= lineBounds.right[0] && lineBounds.left[1] <= lineBounds.right[1]) ||
        (lineBounds.right[0] >= lineBounds.left[0] && lineBounds.right[1] <= lineBounds.left[1])
        ) {
            count += 1;
        }
   }
   printf("count: %d", count);
}
