#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0;

char lookahead() {
    return input[pos];
}

void match(char c) {
    if (lookahead() == c)
        pos++;
    else {
        printf("Error: expected %c at position %d\n", c, pos);
        exit(1);
    }
}

void Expression();  // needed since Factor() calls it

void Factor() {
    if (isdigit(lookahead())) {              // number
        while (isdigit(lookahead()))
            match(lookahead());
    } else if (isalpha(lookahead())) {       // identifier
        while (isalpha(lookahead()))
            match(lookahead());
    } else if (lookahead() == '(') {         // (Expression)
        match('(');
        Expression();
        match(')');
    } else {
        printf("Error: unexpected symbol '%c' at position %d\n", lookahead(), pos);
        exit(1);
    }
}

void TermTail() {
    if (lookahead() == '*') {
        match('*');
        Factor();
        TermTail();
    } else if (lookahead() == '/') {
        match('/');
        Factor();
        TermTail();
    }
    // epsilon → do nothing
}

void Term() {
    Factor();
    TermTail();
}

void ExpressionTail() {
    if (lookahead() == '+') {
        match('+');
        Term();
        ExpressionTail();
    } else if (lookahead() == '-') {
        match('-');
        Term();
        ExpressionTail();
    }
    // epsilon → do nothing
}

void Expression() {
    Term();
    ExpressionTail();
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    Expression();  // Start symbol

    if (lookahead() == '\0')
        printf("Parsing successful!\n");
    else
        printf("Error: extra input at position %d\n", pos);

    return 0;
}