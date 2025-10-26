#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_PROD 10

char production[MAX_PROD][MAX];
int numProductions = 0;

char input[MAX];
char stack[MAX];
int sp = -1;  // stack pointer
int ipPos = 0; // input pointer

void push(char c) {
    stack[++sp] = c;
    stack[sp + 1] = '\0';
}

void pop(int n) {
    sp -= n;
    if (sp < -1) sp = -1;
    stack[sp + 1] = '\0';
}

// Check if top of stack matches RHS of production
int matchRHS(const char *rhs) {
    int len = strlen(rhs);
    if (sp + 1 < len)
        return 0;
    for (int i = 0; i < len; i++) {
        if (stack[sp - len + 1 + i] != rhs[i])
            return 0;
    }
    return 1;
}

// Try to reduce the stack using any production
int reduce() {
    char action[50];
    for (int p = 0; p < numProductions; p++) {
        char lhs = production[p][0];
        char *rhs = production[p] + 2; // skip '='

        if (matchRHS(rhs)) {
            int len = strlen(rhs);
            pop(len);
            push(lhs);

            sprintf(action, "REDUCE: %c -> %s", lhs, rhs);
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

    printf("Enter productions (e.g., E=E+E, E=i):\n");
    for (int i = 0; i < numProductions; i++) {
        scanf("%s", production[i]);
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

        // Try reducing repeatedly
        while (reduce());
    }

    // Final reductions after input is consumed
    while (reduce());

    char startSymbol = production[0][0];
    if (sp == 1 && stack[sp] == startSymbol && stack[0] == '$')
        printf("\nInput string is successfully parsed!\n");
    else
        printf("\nInput string is rejected!\n");

    return 0;
}