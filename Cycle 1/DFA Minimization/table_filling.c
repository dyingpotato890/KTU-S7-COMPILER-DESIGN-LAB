#include<stdio.h>

int main() {
    int numSymbols, numStates;
    int transition[10][10];
    int numFinalStates, isFinalState[10];
    int distinguishable[10][10];
    
    printf("Enter no. of states: ");
    scanf("%d", &numStates);
    printf("Enter no. of symbols: ");
    scanf("%d", &numSymbols);

    printf("Enter transition table:\n");
    for(int state=0; state<numStates; state++)
        for(int symbol=0; symbol<numSymbols; symbol++)
            scanf("%d", &transition[state][symbol]);

    printf("Enter no. of final states: ");
    scanf("%d", &numFinalStates);
    
    for(int state=0; state<numStates; state++)
        isFinalState[state] = 0;
        
    printf("Enter final states:\n");
    for(int i=0; i<numFinalStates; i++) {
        int finalState;
        scanf("%d", &finalState);
        isFinalState[finalState] = 1;
    }

    // Initialize distinguishability
    for(int i=0; i<numStates; i++)
        for(int j=0; j<numStates; j++)
            distinguishable[i][j] = (isFinalState[i] != isFinalState[j]);

    // Find distinguishable pairs
    int updated = 1;
    while(updated) {
        updated = 0;
        for(int s1=0; s1<numStates; s1++) {
            for(int s2=s1+1; s2<numStates; s2++) {
                if(!distinguishable[s1][s2]) {
                    for(int sym=0; sym<numSymbols; sym++) {
                        int next1 = transition[s1][sym], next2 = transition[s2][sym];
                        if(distinguishable[next1][next2]) {
                            distinguishable[s1][s2] = distinguishable[s2][s1] = 1;
                            updated = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Merge equivalent states
    int stateGroup[10];
    for(int i=0; i<numStates; i++)
        stateGroup[i] = i;
        
    for(int i=0; i<numStates; i++)
        for(int j=0; j<i; j++)
            if(!distinguishable[i][j] && stateGroup[i] != stateGroup[j]) {
                int oldGroup = stateGroup[i];
                for(int k=0; k<numStates; k++)
                    if(stateGroup[k] == oldGroup)
                        stateGroup[k] = stateGroup[j];
            }

    // Print equivalent classes
    printf("\nEquivalent Classes:\n");
    int printed[10] = {0};
    for(int i=0; i<numStates; i++) {
        if(!printed[stateGroup[i]]) {
            printed[stateGroup[i]] = 1;
            printf("{");
            int first = 1;
            for(int j=0; j<numStates; j++) {
                if(stateGroup[j] == stateGroup[i]) {
                    if(!first) printf(", ");
                    printf("%d", j);
                    first = 0;
                }
            }
            printf("}\n");
        }
    }

    // Print minimized DFA
    printf("\nMinimized DFA:\n");
    for(int i=0; i<10; i++) printed[i] = 0;
    
    for(int i=0; i<numStates; i++) {
        if(!printed[stateGroup[i]]) {
            printed[stateGroup[i]] = 1;
            printf("State %d: ", stateGroup[i]);
            for(int sym=0; sym<numSymbols; sym++)
                printf("%d ", stateGroup[transition[i][sym]]);
            printf("\n");
        }
    }

    return 0;
}