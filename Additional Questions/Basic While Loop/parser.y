%{
    #include <stdio.h>
    
    int yylex(void);
    void yyerror(const char *s);

    int valid = 0;
%}

%token WHILE LPAREN RPAREN LBRACE RBRACE SEMICOLON ASSIGN LT GT LE GE EQ INC DEC
%token ID NUMBER

%%

start: WHILE LPAREN cond RPAREN LBRACE body SEMICOLON RBRACE    {valid = 1;};

cond: expr relop expr
    | ID INC
    | ID DEC;

body: ID ASSIGN expr

expr: ID | NUMBER
relop: LT | GT | LE | GE | EQ

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERROR!");
}

int main() {
    printf("Enter The While Loop: ");
    yyparse();

    if (valid)
        printf("\nVALID While Loop");
    else
        printf("\nINVALID While Loop");
}