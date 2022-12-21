#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


int main() {
	FILE* input = fopen("./1_input.txt", "r");

	if (! input) {
		printf("oops could not read file");
		exit(-1);
	}


	char *line = (char *) malloc(256); //short strings

	//read the file 256 bytes at a time.
	struct Stack *stack = (struct Stack*) malloc(sizeof(struct Stack));
	int max = -1;
	int currentSum = 0;
	while (fgets(line, 256, input) != NULL) {
		//search through bytes to find \n delimited strings
		for(size_t i = 0; i < strlen(line); i++) {
			char theChar = line[i];
			if (stack->head == NULL) {
				//allocate head if NULL
				stack->head = (struct StackNode*) malloc(sizeof(struct StackNode));
				stack->head->next = NULL;
			}

			//reset when we hit line with an empty stack
			if (stack->head->next == NULL && theChar == '\n') {
				printf("sum: %d\n", currentSum);
				if (currentSum > max) {
					max = currentSum;
				}
				currentSum = 0;
				continue;
			}
			
			//linesum
			if (theChar == '\n') {
				int digit = 1;
				int sum = 0;
				while(stack->head != NULL) {
					char popped = pop(stack);
					sum += digit * atoi(&popped);
					digit *= 10;
				}
				currentSum += sum;
				continue;
			}
			push(stack, theChar);
		}
	}
	printf("max: %d\n", max);
}

