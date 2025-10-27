#include <stdio.h>
#include <string.h>

#define MAX 50

int idx(char c, char terminals[], int n) {
    for (int i = 0; i < n; i++) {
        if (terminals[i] == c)
            return i;
    }
    return -1;
}

int is_operator(char c) {
    return (c != 'i' && c != '$');
}

// Function to get the topmost valid symbol from the stack
char get_top_symbol(char stack[], int top) {
    while (top >= 0) {
        if (stack[top] != '<' && stack[top] != '>' && stack[top] != '=')
            return stack[top];
        top--;
    }
    return '$';
}

int main() {
    char stack[MAX], input[MAX], opt[10][10][1], terminals[10];
    int i, j, k, numTerminals, top = 0, col, row;

    // Initialize arrays
    for (i = 0; i < 10; i++) {
        stack[i] = '\0';
        input[i] = '\0';
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = '\0';
        }
    }

    // Read number of terminals and their symbols
    printf("Enter the number of terminals: ");
    scanf("%d", &numTerminals);

    printf("Enter the terminals: ");
    scanf("%s", terminals);

    // Read operator precedence table
    printf("\nEnter the table values (<, >, =):\n");
    for (i = 0; i < numTerminals; i++) {
        for (j = 0; j < numTerminals; j++) {
            printf("Enter the value for (%c, %c): ", terminals[i], terminals[j]);
            scanf("%s", opt[i][j]);
        }
    }

    // Display operator precedence table
    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n\t");
    for (i = 0; i < numTerminals; i++)
        printf("%c\t", terminals[i]);
    printf("\n");

    for (i = 0; i < numTerminals; i++) {
        printf("%c\t", terminals[i]);
        for (j = 0; j < numTerminals; j++)
            printf("%c\t", opt[i][j][0]);
        printf("\n");
    }

    // Initialize stack
    stack[top] = '$';

    printf("\nEnter the input string (e.g., i+i*i): ");
    scanf("%s", input);

    // Add end marker if not included
    if (input[strlen(input) - 1] != '$')
        strcat(input, "$");

    // Check for consecutive operators
    for (i = 0; i < strlen(input) - 1; i++) {
        if (is_operator(input[i]) && is_operator(input[i + 1]) &&
            input[i] != '$' && input[i + 1] != '$') {
            printf("\nError: consecutive operators '%c%c' in input\n", input[i], input[i + 1]);
            return 0;
        }
    }

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("%s\t\t%s\t\t", stack, input);

    i = 0;
    while (1) {
        char a = get_top_symbol(stack, top);
        char b = input[i];

        col = idx(a, terminals, numTerminals);
        row = idx(b, terminals, numTerminals);

        if (col == -1 || row == -1) {
            printf("\nError: invalid symbol '%c'\n", (col == -1) ? a : b);
            break;
        }

        if (a == '$' && b == '$') {
            printf("String ACCEPTED\n");
            break;
        } else if (opt[col][row][0] == '<' || opt[col][row][0] == '=') {
            stack[++top] = opt[col][row][0];
            stack[++top] = b;
            stack[top + 1] = '\0';
            printf("Shift %c\n", b);
            i++;
        } else if (opt[col][row][0] == '>') {
            while (top > 0 && stack[top] != '<')
                top--;
            if (top > 0)
                top--;
            stack[top + 1] = '\0';
            printf("Reduce\n");
        } else {
            printf("\nError: invalid precedence relation between '%c' and '%c'\n", a, b);
            break;
        }

        printf("%s\t\t", stack);
        for (k = i; k < strlen(input); k++)
            printf("%c", input[k]);
        printf("\t\t");
    }

    return 0;
}