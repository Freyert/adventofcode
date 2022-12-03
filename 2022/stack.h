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
