#include <stdio.h>
#include <string.h>

// Generate three-address code for a specific operator in the expression
void gen_code_for_operator(char *inp, char operator, char *reg) {
    int i = 0, j = 0;
    char temp[100];  // temporary string to build the new expression after replacing operands

    while (inp[i] != '\0') {
        if (inp[i] == operator) {
            printf("%c\t%c\t%c\t%c\n", operator, *reg, inp[i - 1], inp[i + 1]);

            // Replace the evaluated sub-expression in temp with the destination register
            temp[j - 1] = *reg;

            i += 2;      // Skip over the operator and the right operand
            (*reg)--;    // Move to next available register (e.g., Z -> Y)
            continue;
        }
        temp[j] = inp[i];  // Copy the character if it's not the current operator
        i++;
        j++;
    }
    temp[j] = '\0';
    strcpy(inp, temp); // Update the expression with evaluated parts replaced by registers
}

// Generate three-address code for the entire expression based on operator precedence
void gen_code(char *inp) {
    char reg = 'Z';  // Start assigning temporary results from register Z

    // Apply operator precedence: first '/', then '*', then '+', then '-', then '='
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main() {
    char inp[100];

    printf("Enter expression:\n\n");
    scanf("%s", inp);

    printf("Op\tDestn\tArg1\tArg2\n");
    gen_code(inp);

    return 0;
}