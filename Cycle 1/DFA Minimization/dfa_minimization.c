#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Transition table: state × symbol → next state
int transitionTable[MAX][MAX];
int numStates, numSymbols;
int finalStates[MAX], finalCount;
int startState;

// Partition arrays
int partition[MAX], newPartition[MAX];

// Check if two states are distinguishable
int isDifferent(int state1, int state2) {
  return finalStates[state1] != finalStates[state2];
}

int main() {
  printf("Enter The Number of States: ");
  scanf("%d", &numStates);

  printf("Enter The Number of Symbols: ");
  scanf("%d", &numSymbols);

  printf("Enter Transition Table (%d x %d):\n", numStates, numSymbols);
  for (int i = 0; i < numStates; i++) {
    for (int j = 0; j < numSymbols; j++) {
      scanf("%d", &transitionTable[i][j]);
    }
  }

  printf("Enter The Start State: ");
  scanf("%d", &startState);

  printf("Enter The Number of Final States: ");
  scanf("%d", &finalCount);

  memset(finalStates, 0, sizeof(finalStates));
  printf("Enter Final States: ");
  for (int i = 0; i < finalCount; i++) {
    int f;
    scanf("%d", &f);
    finalStates[f] = 1;
  }

  // Initial partition: 1 for final, 0 for non-final
  for (int i = 0; i < numStates; i++) {
    partition[i] = finalStates[i] ? 1 : 0;
  }

  int changed;
  do {
    changed = 0;
    int newClass = 0;
    for (int i = 0; i < numStates; i++)
      newPartition[i] = -1;

    for (int i = 0; i < numStates; i++) {
      if (newPartition[i] == -1) {
        newPartition[i] = newClass;
        for (int j = i + 1; j < numStates; j++) {
          if (partition[i] == partition[j]) {
            int same = 1;
            for (int s = 0; s < numSymbols; s++) {
              if (partition[transitionTable[i][s]] !=
                  partition[transitionTable[j][s]]) {
                same = 0;
                break;
              }
            }
            if (same)
              newPartition[j] = newClass;
          }
        }
        newClass++;
      }
    }

    // Check if any partition changed
    for (int i = 0; i < numStates; i++) {
      if (partition[i] != newPartition[i]) {
        changed = 1;
        break;
      }
    }

    for (int i = 0; i < numStates; i++)
      partition[i] = newPartition[i];

  } while (changed);

  // Count minimized DFA states
  int numClasses = 0;
  for (int i = 0; i < numStates; i++) {
    if (partition[i] > numClasses)
      numClasses = partition[i];
  }
  numClasses++;

  printf("\nMinimized DFA has %d states:\n", numClasses);
  for (int i = 0; i < numClasses; i++) {
    printf("State %d: {", i);
    for (int j = 0; j < numStates; j++)
      if (partition[j] == i)
        printf(" %d ", j);
    printf("}\n");
  }

  printf("\nTransitions in Minimized DFA:\n");
  for (int i = 0; i < numClasses; i++) {
    for (int s = 0; s < numSymbols; s++) {
      int representative = -1;
      for (int j = 0; j < numStates; j++) {
        if (partition[j] == i) {
          representative = j;
          break;
        }
      }
      if (representative != -1) {
        printf("%d --%d--> %d\n", i, s,
               partition[transitionTable[representative][s]]);
      }
    }
  }

  printf("\nStart State: %d\n", partition[startState]);
  printf("Final States: ");
  for (int i = 0; i < numStates; i++) {
    if (finalStates[i] && partition[i] != -1) {
      printf("%d ", partition[i]);
    }
  }
  printf("\n");

  return 0;
}
