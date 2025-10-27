#include <stdio.h>
#include <string.h>

void main() {
    char stack[20], input[20], opt[10][10][1], terminals[10];
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

    // Initialize stack and input string (already includes $ at end)
    stack[top] = '$';

    printf("\nEnter the input string: ");
    scanf("%s", input);
    i = 0;

    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, input);

    // Operator precedence parsing loop
    while (i <= strlen(input)) {
        // Find column and row for stack top and current input symbol
        for (k = 0; k < numTerminals; k++) {
            if (stack[top] == terminals[k])
                col = k;
            if (input[i] == terminals[k])
                row = k;
        }

        if ((stack[top] == '$') && (input[i] == '$')) {
            printf("String is ACCEPTED\n");
            break;
        }
        else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '=')) {
            stack[++top] = opt[col][row][0];
            stack[++top] = input[i];
            printf("Shift %c", input[i]);
            i++;
        }
        else {
            if (opt[col][row][0] == '>') {
                while (stack[top] != '<')
                    --top;
                top = top - 1;
                printf("Reduce");
            } else {
                printf("\nString is NOT accepted");
                break;
            }
        }

        // Display current stack and input
        printf("\n");
        for (k = 0; k <= top; k++)
            printf("%c", stack[k]);
        printf("\t\t\t");
        for (k = i; k < strlen(input); k++)
            printf("%c", input[k]);
        printf("\t\t\t");
    }
}