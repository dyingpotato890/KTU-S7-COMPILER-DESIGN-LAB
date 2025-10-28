#include <stdio.h>
#include <string.h>

char input[50];
int pos = 0;

int parseExpression(); // E
int parseTerm();       // T
int parseFactor();     // F
int parseMoreExpressions(); // E'
int parseMoreTerms();  // T'

// Match a specific symbol
int match(char expected) {
    if (input[pos] == expected) {
        printf("Matched '%c'\n", expected);
        pos++;
        return 1;
    }
    return 0;
}

// F → i | (E)
int parseFactor() {
    printf("F -> i | (E)\n");
    if (match('i'))
        return 1;
    if (match('(')) {
        if (parseExpression() && match(')'))
            return 1;
        return 0;
    }
    return 0;
}

// T' → * F T' | e
int parseMoreTerms() {
    if (input[pos] == '*') {
        printf("T' -> * F T'\n");
        match('*');
        if (parseFactor() && parseMoreTerms())
            return 1;
        return 0;
    }
    printf("T' -> e\n");
    return 1;
}

// T → F T'
int parseTerm() {
    printf("T -> F T'\n");
    if (parseFactor() && parseMoreTerms())
        return 1;
    return 0;
}

// E' → + T E' | e
int parseMoreExpressions() {
    if (input[pos] == '+') {
        printf("E' -> + T E'\n");
        match('+');
        if (parseTerm() && parseMoreExpressions())
            return 1;
        return 0;
    }
    printf("E' -> e\n");
    return 1;
}

// E → T E'
int parseExpression() {
    printf("E -> T E'\n");
    if (parseTerm() && parseMoreExpressions())
        return 1;
    return 0;
}

int main() {
    printf("Grammar:\n");
    printf("E  -> T E'\nE' -> + T E' | e\nT  -> F T'\nT' -> * F T' | e\nF  -> (E) | i\n\n");

    printf("Enter expression: ");
    scanf("%s", input);

    printf("\n--- Parsing Steps ---\n");
    if (parseExpression() && input[pos] == '\0')
        printf("\n Accepted  valid expression\n");
    else
        printf("\n Rejected  invalid expression\n");
    return 0;
}