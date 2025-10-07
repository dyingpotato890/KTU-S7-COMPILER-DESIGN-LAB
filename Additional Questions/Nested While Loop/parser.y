%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token WHILE LPAREN RPAREN LBRACE RBRACE SEMICOLON ASSIGN LT GT LE GE EQ INC DEC
%token ID NUMBER

/* Operator precedence (lowest → highest) */
%right ASSIGN
%left EQ
%left LT GT LE GE
%left INC DEC

%%

program : stmt_list
        ;

stmt_list : stmt
          | stmt_list stmt
          ;

stmt : while_stmt
     | assn_stmt SEMICOLON
     | expr_stmt SEMICOLON
     ;

while_stmt : WHILE LPAREN condition RPAREN LBRACE stmt_list RBRACE
           { printf("Recognized WHILE loop\n"); }
           ;

condition : expr ;  /* a condition is just an expression now */

assn_stmt : ID ASSIGN expr ;

expr_stmt : ID INC
          | ID DEC
          ;

expr : ID
     | NUMBER
     | ID ASSIGN expr
     | expr LT expr
     | expr GT expr
     | expr LE expr
     | expr GE expr
     | expr EQ expr
     ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter C-style WHILE loop code:\n");
    yyparse();
    return 0;
}