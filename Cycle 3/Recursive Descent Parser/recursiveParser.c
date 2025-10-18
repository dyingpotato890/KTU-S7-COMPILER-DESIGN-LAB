#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char input[50];
int inputPtr = 0;
char derivation[100], temp[100];
int n = 0;

void Expression();
void ExpressionPrime();
void Term();
void TermPrime();
void Factor();
void advance();

void advance() {
    inputPtr++;
}

void Expression() {
    strcpy(derivation, "TE'");
    printf("E = %-25s", derivation);
    printf("E -> TE'\n");

    Term();
    ExpressionPrime();
}

void ExpressionPrime() {
    int i, n = 0, len;
    for (i = 0; i <= strlen(derivation); i++)
        if (derivation[i] != 'e')
            temp[n++] = derivation[i];
    temp[n] = '\0';
    strcpy(derivation, temp);
    len = strlen(derivation);

    for (n = 0; n < len && derivation[n] != 'E'; n++);

    if (input[inputPtr] == '+') {
        i = n + 2;
        while (i <= len) {
            derivation[i + 2] = derivation[i];
            i++;
        }

        derivation[n++] = '+';
        derivation[n++] = 'T';
        derivation[n++] = 'E';
        derivation[n++] = '\'';
        derivation[len + 3] = '\0';

        printf("E = %-25s", derivation);
        printf("E' -> +TE'\n");

        advance();
        Term();
        ExpressionPrime();
    } else {
        derivation[n] = 'e';
        derivation[n + 1] = '\0';
        printf("E = %-25s", derivation);
        printf("E' -> e\n");
    }
}

void Term() {
    int i, n = 0, len;
    for (i = 0; i <= strlen(derivation); i++)
        if (derivation[i] != 'e')
            temp[n++] = derivation[i];
    temp[n] = '\0';
    strcpy(derivation, temp);
    len = strlen(derivation);

    for (n = 0; n < len && derivation[n] != 'T'; n++);

    i = n + 1;
    while (i < len) {
        derivation[i + 2] = derivation[i];
        i++;
    }

    derivation[n++] = 'F';
    derivation[n++] = 'T';
    derivation[n++] = '\'';
    derivation[len + 3] = '\0';

    printf("E = %-25s", derivation);
    printf("T -> FT'\n");

    Factor();
    TermPrime();
}

void TermPrime() {
    int i, n = 0, len;
    for (i = 0; i <= strlen(derivation); i++)
        if (derivation[i] != 'e')
            temp[n++] = derivation[i];
    temp[n] = '\0';
    strcpy(derivation, temp);
    len = strlen(derivation);

    for (n = 0; n < len && derivation[n] != 'T'; n++);

    if (input[inputPtr] == '*') {
        i = n + 2;
        while (i < len) {
            derivation[i + 2] = derivation[i];
            i++;
        }

        derivation[n++] = '*';
        derivation[n++] = 'F';
        derivation[n++] = 'T';
        derivation[n++] = '\'';
        derivation[len + 3] = '\0';

        printf("E = %-25s", derivation);
        printf("T' -> *FT'\n");

        advance();
        Factor();
        TermPrime();
    } else {
        derivation[n] = 'e';
        derivation[n + 1] = '\0';
        printf("E = %-25s", derivation);
        printf("T' -> e\n");
    }
}

void Factor() {
    int i, n = 0, len;
    for (i = 0; i <= strlen(derivation); i++)
        if (derivation[i] != 'e')
            temp[n++] = derivation[i];
    temp[n] = '\0';
    strcpy(derivation, temp);
    len = strlen(derivation);

    for (n = 0; n < len && derivation[n] != 'F'; n++);

    if (input[inputPtr] == 'i' || input[inputPtr] == 'I') {
        derivation[n] = 'i';
        derivation[n + 1] = '\0';
        printf("E = %-25s", derivation);
        printf("F -> i\n");
        advance();
    } else if (input[inputPtr] == '(') {
        advance();
        Expression();
        if (input[inputPtr] == ')') {
            advance();
            derivation[n++] = '(';
            derivation[n++] = 'E';
            derivation[n++] = ')';
            derivation[n] = '\0';
            printf("E = %-25s", derivation);
            printf("F -> (E)\n");
        } else {
            printf("\nSyntax Error: Missing ')'\n");
            exit(1);
        }
    } else {
        printf("\nSyntax Error: Invalid Factor\n");
        exit(1);
    }
}

int main() {
    printf("\nGrammar Without Left Recursion:\n");
    printf("\tE  -> TE'\n");
    printf("\tE' -> +TE' | e\n");
    printf("\tT  -> FT'\n");
    printf("\tT' -> *FT' | e\n");
    printf("\tF  -> (E) | i\n");

    printf("\nEnter The Input Expression: ");
    scanf("%s", input);

    printf("\nDerivation Steps:\n");
    printf("E\n");

    Expression();

    printf("\nParsing Completed Successfully.\n");
    return 0;
}