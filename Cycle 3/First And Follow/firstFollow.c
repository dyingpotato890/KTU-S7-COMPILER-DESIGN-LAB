#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX], firstSet[MAX][MAX], followSet[MAX][MAX];
int n; // number of productions

int addToSet(char *set, char c) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == c)
            return 0;
    }
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
    return 1;
}

void findFirst(char *result, char c) {
    if (!isupper(c)) {
        addToSet(result, c); // terminal
        return;
    }

    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            if (production[i][2] == '#') { // epsilon
                addToSet(result, '#');
            } else {
                int j = 2;
                while (production[i][j] != '\0') {
                    char next = production[i][j];
                    if (!isupper(next)) {
                        addToSet(result, next);
                        break;
                    } else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        int hasEpsilon = 0;
                        for (int k = 0; temp[k] != '\0'; k++) {
                            if (temp[k] != '#')
                                addToSet(result, temp[k]);
                            else
                                hasEpsilon = 1;
                        }
                        if (!hasEpsilon) break;
                        j++;
                        if (production[i][j] == '\0')
                            addToSet(result, '#');
                    }
                }
            }
        }
    }
}

void findFollow(char *result, char c) {
    if (production[0][0] == c) {
        addToSet(result, '$'); // add $ to start symbol
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    char next = production[i][j + 1];
                    if (!isupper(next)) {
                        addToSet(result, next);
                    } else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        int hasEpsilon = 0;
                        for (int k = 0; temp[k] != '\0'; k++) {
                            if (temp[k] != '#')
                                addToSet(result, temp[k]);
                            else
                                hasEpsilon = 1;
                        }
                        if (hasEpsilon) {
                            char temp2[MAX] = "";
                            findFollow(temp2, production[i][0]);
                            for (int k = 0; temp2[k] != '\0'; k++)
                                addToSet(result, temp2[k]);
                        }
                    }
                } else if (production[i][0] != c) {
                    char temp[MAX] = "";
                    findFollow(temp, production[i][0]);
                    for (int k = 0; temp[k] != '\0'; k++)
                        addToSet(result, temp[k]);
                }
            }
        }
    }
}

int main() {
    int i;
    char first[MAX], follow[MAX];
    char c;

    printf("Enter Number of Productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter Productions (like E=E+T or T=T*F):\n");
    for (i = 0; i < n; i++) {
        fgets(production[i], MAX, stdin);
        for (int j = 0; production[i][j] != '\0'; j++) {
            if (production[i][j] == '\n') {
                production[i][j] = '\0';
                break;
            }
        }
    }

    printf("\nFIRST and FOLLOW sets:\n");

    for (i = 0; i < n; i++) {
        c = production[i][0]; // Left-hand side non-terminal
        memset(first, 0, sizeof(first));
        memset(follow, 0, sizeof(follow));

        findFirst(first, c);
        findFollow(follow, c);

        printf("\n%c:\n", c);
        printf("FIRST(%c) = { ", c);
        for (int j = 0; first[j] != '\0'; j++)
            printf("%c ", first[j]);
        printf("}\n");

        printf("FOLLOW(%c) = { ", c);
        for (int j = 0; follow[j] != '\0'; j++)
            printf("%c ", follow[j]);
        printf("}\n");
    }

    return 0;
}