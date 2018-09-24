#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack
{
	int top;
	char *array;
};

int precedence(char c)
{
	switch(c)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
	}
	return -1;
}

struct Stack *createStack(int capacity)
{
	struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
	stack->top = -1;
	stack->array = (char *)malloc(sizeof(char) * capacity);
	return stack;
}

void push(struct Stack *stack, char c)
{
	stack->array[stack->top+1] = c;
	stack->top++;
}

char pop(struct Stack *stack)
{
	if(stack->top == -1) return '#';
	char c = stack->array[stack->top];
	stack->top--;
	return c;
}

bool isAlpha(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	return false;
}

char peek(struct Stack *stack)
{
	if(stack->top != -1)
		return stack->array[stack->top];
}

void infixToPostfix(char *infix, int len)
{
	struct Stack *stack = createStack(100);
	char *postfix = (char *)malloc(100);
	int k = 0;
	for(int i = 0; i < len; i++)
	{
		char current = infix[i];

		if(current == '(')
			push(stack, current);

		if(current == ')')
		{
			while(peek(stack) != '(')
			{
				char popped = pop(stack);
				postfix[k++] = popped;
			}
			pop(stack);
		}

		if(isAlpha(current))
			postfix[k++] = current;
		else
		{
			if(stack->top == -1 || (precedence(current) > precedence(peek(stack))))
			{
				push(stack, current);
			}
			else
			{
				while(precedence(peek(stack)) > precedence(current))
				{
					char popped = pop(stack);
					postfix[k++] = popped;
				}
			}
		}
	}

	while(stack->top != -1)
	{
		char popped = pop(stack);
		postfix[k++] = popped;
	}
	postfix[k++] = '$';

	printf("Postfix Expression: %s\n", postfix);

}

int main()
{
	char *infix = "a+(b*(c+d)+e)+f";
	int len = 15;
	infixToPostfix(infix, len);
	return 0;
}
