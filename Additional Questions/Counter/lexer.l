%{
    #include <stdio.h>    

    int characters = 0;
    int words = 0;
    int lines = 0;
%}

%%

[a-zA-Z]+       {words += 1; characters += yyleng;}
\n              {lines += 1;}
[ ]+


%%

int main() {
    printf("\nEnter The Text: ");
    yylex();
    printf("No. Of Characters: %d\nNo. Of Words: %d\nNo. Of Lines: %d\n", characters, words, lines);
    return 0;
}