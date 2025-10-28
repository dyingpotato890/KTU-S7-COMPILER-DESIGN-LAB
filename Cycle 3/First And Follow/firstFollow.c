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

void findFollowHelper(char *result, char c, char *visited) {
    // Check if already computing FOLLOW for this non-terminal
    for (int i = 0; visited[i] != '\0'; i++) {
        if (visited[i] == c)
            return; // Already visited, stop recursion
    }
    
    // Mark as visited
    int len = strlen(visited);
    visited[len] = c;
    visited[len + 1] = '\0';

    // Rule 1: If c is start symbol, add $ to FOLLOW
    if (production[0][0] == c) {
        addToSet(result, '$'); // add $ to start symbol
    }

    // Rule 2 & 3: Look for c in RHS of all productions
    for (int i = 0; i < n; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                // Rule 2: If A -> αcβ, add FIRST(β) - {ε} to FOLLOW(c)
                if (production[i][j + 1] != '\0') {
                    char next = production[i][j + 1];
                    if (!isupper(next)) {
                        // next is terminal, add it directly
                        addToSet(result, next);
                    } else {
                        // next is non-terminal, find its FIRST set
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        int hasEpsilon = 0;
                        for (int k = 0; temp[k] != '\0'; k++) {
                            if (temp[k] != '#')
                                addToSet(result, temp[k]);
                            else
                                hasEpsilon = 1;
                        }
                        // Rule 3: If ε in FIRST(β), add FOLLOW(A) to FOLLOW(c)
                        if (hasEpsilon && production[i][0] != c) {
                            findFollowHelper(result, production[i][0], visited);
                        }
                    }
                } else if (production[i][0] != c) {
                    // Rule 3: If A -> αc (c is at end), add FOLLOW(A) to FOLLOW(c)
                    findFollowHelper(result, production[i][0], visited);
                }
            }
        }
    }
}

void findFollow(char *result, char c) {
    char visited[MAX] = "";
    findFollowHelper(result, c, visited);
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