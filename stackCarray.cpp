#include <stdio.h>
#include <string.h>
#define SIZE 100

struct Stack
{
    int data[SIZE];
    int top;
};

int push(struct Stack *stack, int data)
{
    if (stack->top == SIZE - 1)
    {
        return -1;
    } else {
        stack->data[++stack->top] = data;//first move top, then put data in
        return 1;
    }
}

int *pop(struct Stack *stack)
{
    if (stack->top == 0)
    {
        return NULL;
    } else {
        int *data = &stack->data[stack->top];
        stack->top--;
        return data;
    }
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.top = 0;
    while (1)
    {
        scanf("%s", command);
        if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else if (strcmp(command, "push") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if (push(&stack, data) == 1)
            {
                printf("Successfully push data %d into stack.\n");
            }
            else
            {
                printf("Failed to push data into stack.\n");
            }
        }
        else if (strcmp(command, "pop") == 0)
        {
            temp = pop(&stack);
            if (temp == NULL)
            {
                printf("Failed to pop a data from stack.\n");
            }
            else
            {
                printf("Pop data %d from stack.\n", *temp);
            }
        }
    }
}