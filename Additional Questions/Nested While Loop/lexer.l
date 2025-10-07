%{
    #include "y.tab.h"
%}

%%

"while"             { return WHILE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
";"                 { return SEMICOLON; }
"=="                { return EQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return LT; }
">"                 { return GT; }
"="                 { return ASSIGN; }
"++"                { return INC; }
"--"                { return DEC; }

[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }

[ \t\n]+            ;   // ignore whitespace
.                   { /* ignore any unknown character */ }

%%

int yywrap() { 
    return 1; 
}