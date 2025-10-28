%{
    #include <stdio.h>
    char inp[20];
%}

%%

abc {printf("123");}
[ \n\t] ;
.   {printf("%c", yytext[0]);}

%%

int yywrap(void){
    return 1;
}

int main(){
    printf("Enter The String: ");
    yylex();
    scanf("%s", inp);
    return 0;
}