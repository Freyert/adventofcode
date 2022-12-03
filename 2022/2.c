#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//open file
//my total score
//read from file
//map opponent move to value
//map my move to value
//check outcome
//reset

//These constants are used to "normalize"
//input values so that they can be compared without
//needing a "mapping".
//theirs 
//A -> Rock 65 - 64 = 1
//B -> Paper 66 - 64 = 2
//C -> Scissors 67 - 64 = 3

//mine
//X -> Rock 88 - 87 = 1
//Y -> Paper 89 - 87 = 2
//Z -> Scissors 90 - 87 = 3
#define THEIRS 64
#define MINE 87
#define ROCK 1
#define PAPER 2
#define SCISSORS 3

int calculate(char theirs , char mine) {
    int theirChoice = theirs - THEIRS;
    int myChoice = mine - MINE;

    //tie
    if (myChoice == theirChoice) {
        return myChoice + 3;
    }

    //win
    //maybe there's something that could be done with shifting?
    // rock paper scissors
    //        rock  paper    -> (rollover) scissors
    if (
        (theirChoice == ROCK && myChoice == PAPER) ||
        (theirChoice == PAPER && myChoice == SCISSORS) ||
        (theirChoice == SCISSORS && myChoice == ROCK)
     ) {
        return myChoice + 6;
    }




    //loss
    return myChoice;
}

int main() {
	FILE* input = fopen("./2_input.txt", "r");

	if (! input) {
		printf("oops could not read file");
		exit(-1);
	}

    char *buff = (char *) malloc(256);

    int scoreAllRounds = 0;
    char left;
    char right;
    int filePos = 0; //use this to keep track of our parsing state
    while (fgets(buff, 256, input) != NULL) {
        for (size_t i = 0; i < strlen(buff); i++) {
            int parseState = filePos % 4;
            if (parseState == 0) {
                left = buff[i];
            }
            //1 is a space

            if (parseState == 2) {
                right = buff[i];
            }

            //3 is a new line
            if (parseState == 3) {
                int score = calculate(left, right);
                scoreAllRounds += score; 
                printf("%c %c %d %d\n", left, right, score, scoreAllRounds);
            }
            filePos += 1;
        }
    }
    printf("%d\n", scoreAllRounds);
}
