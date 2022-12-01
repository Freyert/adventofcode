#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//push characters in from left to right
//pop them from right to left
struct StackNode {
	struct StackNode *next;
	char value;
};

struct Stack {
	struct StackNode *head;
};

//push an element on the stack.
void push(struct Stack *stack, char c) {
	struct StackNode *el;

	el = (struct StackNode *)malloc(sizeof(struct StackNode));

	el->value = c;
	el->next = stack->head;
	stack->head = el;
};

char pop(struct Stack *stack) {
	char result = ' ';
	if (stack == NULL) {
		return result;
	}

	if (stack->head == NULL) {
		return result;
	}


	struct StackNode *old;
	old = stack->head;
	result = old->value;
	stack->head = stack->head->next;
	free(old);
	return result;
};


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

