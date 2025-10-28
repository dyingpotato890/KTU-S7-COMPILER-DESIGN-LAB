#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX], input[MAX];
int top = -1, pos = 0;

void reduce();

int main() {
    printf("Grammar:\nE → E+E | E*E | (E) | id\n");
    printf("\nEnter input string: ");
    scanf("%s", input);

    printf("\n%-15s %-15s %-15s\n", "STACK", "INPUT", "ACTION");

    while (input[pos] != '\0') {
        // SHIFT
        if (input[pos] == 'i' && input[pos + 1] == 'd') {
            stack[++top] = 'I'; 
            stack[top + 1] = '\0';
            pos += 2;
            printf("%-15s %-15s %-15s\n", stack, input + pos, "SHIFT -> id");
        } else {
            stack[++top] = input[pos++];
            stack[top + 1] = '\0';
            printf("%-15s %-15s %-15s\n", stack, input + pos, "SHIFT");
        }
        // Try to reduce after each shift
        reduce();
    }

    // Final check
    if (top == 0 && stack[top] == 'E')
        printf("\nResult: VALID string \n");
    else
        printf("\nResult: INVALID string \n");
    return 0;
}

void reduce() {
    int changed;
    do {
        changed = 0;
        // REDUCE id → E
        if (top >= 0 && stack[top] == 'I') {
            stack[top] = 'E';
            stack[top + 1] = '\0';
            changed = 1;
            printf("%-15s %-15s %-15s\n", stack, input + pos, "REDUCE -> id");
        }
        // REDUCE E+E → E
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
            top -= 2; stack[top] = 'E'; stack[top + 1] = '\0';
            changed = 1;
            printf("%-15s %-15s %-15s\n", stack, input + pos, "REDUCE -> E+E");
        }
        // REDUCE E*E → E
        else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
            top -= 2; stack[top] = 'E'; stack[top + 1] = '\0';
            changed = 1;
            printf("%-15s %-15s %-15s\n", stack, input + pos, "REDUCE -> E*E");
        }
        // REDUCE (E) → E
        else if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
            top -= 2; stack[top] = 'E'; stack[top + 1] = '\0';
            changed = 1;
            printf("%-15s %-15s %-15s\n", stack, input + pos, "REDUCE -> (E)");
        }
    } while (changed); // Keep reducing until no change
}