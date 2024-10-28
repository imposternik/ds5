#include <ctype.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 

struct Stack* createStack(unsigned capacity) { 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    if (!stack) 
        return NULL; 
    stack->top = -1; 
    stack->capacity = capacity; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    if (!stack->array) 
        return NULL; 
    return stack; 
} 

int isEmpty(struct Stack* stack) { 
    return stack->top == -1; 
} 

int peek(struct Stack* stack) { 
    return stack->array[stack->top]; 
} 

int pop(struct Stack* stack) { 
    if (!isEmpty(stack)) 
        return stack->array[stack->top--]; 
    return -1; 
} 

void push(struct Stack* stack, int op) { 
    stack->array[++stack->top] = op; 
} 

int evaluatePostfix(char* exp) { 
    struct Stack* stack = createStack(strlen(exp)); 
    if (!stack) 
        return -1; 
    for (int i = 0; exp[i]; ++i) { 
        if (isdigit(exp[i])) 
            push(stack, exp[i] - '0'); 
        else { 
            int val1 = pop(stack); 
            int val2 = pop(stack); 
            switch (exp[i]) { 
                case '+': 
                    push(stack, val2 + val1); 
                    break; 
                case '-': 
                    push(stack, val2 - val1); 
                    break; 
                case '*': 
                    push(stack, val2 * val1); 
                    break; 
                case '/': 
                    if (val1 != 0)
                        push(stack, val2 / val1); 
                    else
                        return -1; 
                    break; 
                default:
                    return -1; 
            } 
        } 
    } 
    return pop(stack); 
} 

int main() { 
    char exp[] = "231*+9-"; 
    int result = evaluatePostfix(exp);
    if (result != -1)
        printf("Postfix evaluation: %d\n", result); 
    else
        printf("Error in evaluation.\n");
    
    // Wait for user input before closing (useful in some environments)
    printf("Press Enter to continue...");
    getchar();  // Wait for Enter key

    return 0; 
}
