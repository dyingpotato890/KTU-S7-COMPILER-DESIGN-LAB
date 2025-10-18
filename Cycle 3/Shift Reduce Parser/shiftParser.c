#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_PROD 10

typedef struct {
    char lhs;
    char rhs[20];
} Production;

Production grammar[MAX_PROD];
int numProductions = 0;

char input[MAX];
char stack[MAX];
int sp = -1; // stack pointer
int ipPos = 0; // input pointer

void push(char c) {
    stack[++sp] = c;
    stack[sp + 1] = '\0';
}

void pop(int n) {
    sp -= n;
    stack[sp + 1] = '\0';
}

// Check if top of stack matches RHS of production
int matchRHS(char *rhs) {
    int len = strlen(rhs);
    if (sp + 1 < len) return 0;
    for (int i = 0; i < len; i++) {
        if (stack[sp - len + 1 + i] != rhs[i])
            return 0;
    }
    return 1;
}

// Attempt to reduce stack using any production
int reduce() {
    char action[50];
    for (int p = 0; p < numProductions; p++) {
        if (matchRHS(grammar[p].rhs)) {
            int len = strlen(grammar[p].rhs);
            pop(len);
            push(grammar[p].lhs);

            sprintf(action, "REDUCE: %c -> %s", grammar[p].lhs, grammar[p].rhs);
            printf("%-25s %-25s %-25s\n", stack, input + ipPos, action);
            return 1; // reduced
        }
    }
    return 0; // no reduction possible
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &numProductions);
    getchar();

    printf("Enter productions in format E=E+E (use no spaces):\n");
    for (int i = 0; i < numProductions; i++) {
        char temp[20];
        scanf("%s", temp);
        grammar[i].lhs = temp[0];
        strcpy(grammar[i].rhs, temp + 2); // skip '='
    }

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-25s %-25s %-25s\n", "STACK", "INPUT", "ACTION");
    push('$'); // initial stack symbol

    while (input[ipPos] != '\0') {
        // SHIFT
        char action[50];
        push(input[ipPos]);
        sprintf(action, "SHIFT: %c", input[ipPos]);
        printf("%-25s %-25s %-25s\n", stack, input + ipPos + 1, action);
        ipPos++;

        // Try reducing as much as possible
        while (reduce());
    }

    // Final reductions after input consumed
    while (reduce());

    if (sp == 1 && stack[sp] == grammar[0].lhs)
        printf("\nInput string is successfully parsed!\n");
    else
        printf("\nInput string is rejected!\n");

    return 0;
}