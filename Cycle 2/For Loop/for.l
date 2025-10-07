%{
#include "y.tab.h"
%}

%%

"for"       { return FOR; }
"("         { return LPAREN; }
")"         { return RPAREN; }
";"         { return SEMICOLON; }
"="         { return ASSIGN; }
"<"         { return LT; }
">"         { return GT; }
"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"++"        { return INC; }
"--"        { return DEC; }

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }

[ \t\n]     ;   /* ignore whitespace */
.           { return yytext[0]; }

%%

/*

lex for.l
yacc -d for.y
gcc lex.yy.c y.tab.c -o for
./for

*/