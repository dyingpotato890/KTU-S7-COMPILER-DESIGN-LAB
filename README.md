# KTU S7 Compiler Design Lab

This repository contains the programs and experiments for the S7 Compiler Design Lab, following the KTU 2019 syllabus.

## Table of Contents
- [Setup Instructions](#setup-instructions)
- [List of Experiments](#list-of-experiments)
- [Contributors](#contributors)

## Setup Instructions

1.  **C Compiler:**
    Most of the programs are written in C. Ensure you have a C compiler like GCC installed.
    ```bash
    # For Debian/Ubuntu
    sudo apt-get install gcc
    ```

2.  **Flex and Bison:**
    For experiments involving lexical analysis and parsing (`.l` and `.y` files), you will need `flex` and `bison`.
    ```bash
    # For Debian/Ubuntu
    sudo apt-get install flex bison
    ```

3.  **Clone the Repository:**
    ```bash
    git clone https://github.com/dyingpotato890/KTU-S7-COMPILER-DESIGN-LAB.git
    cd KTU-S7-COMPILER-DESIGN-LAB
    ```

## List of Experiments

The experiments are organized into cycles as per the lab syllabus.

### Cycle 1
- [DFA Minimization](./Cycle%201/DFA%20Minimization/)
- [E NFA To NFA](./Cycle%201/E%20NFA%20To%20NFA/)
- [Epsilon Closure](./Cycle%201/Epsilon%20Closure/)
- [NFA To DFA](./Cycle%201/NFA%20To%20DFA/)

### Cycle 2
- BNF Rules: [Lex](./Cycle%202/BNF%20Rules/lexer.l) | [Yacc](./Cycle%202/BNF%20Rules/parser.y)
- Calculator: [Lex](./Cycle%202/Calculator/calc.l) | [Yacc](./Cycle%202/Calculator/calc.y)
- For Loop: [Lex](./Cycle%202/For%20Loop/for.l) | [Yacc](./Cycle%202/For%20Loop/for.y)
- [Lexical Analyzer](./Cycle%202/Lexical%20Analyzer/)
- [No Name](./Cycle%202/No%20Name/)
- Valid Variable: [Lex](./Cycle%202/Valid%20Variable/lexer.l) | [Yacc](./Cycle%202/Valid%20Variable/parser.y)

### Cycle 3
- [First And Follow](./Cycle%203/First%20And%20Follow/)
- [Operator Precedance](./Cycle%203/Operator%20Precedance/)
- [Recursive Descent Parser](./Cycle%203/Recursive%20Descent%20Parser/)
- [Shift Reduce Parser](./Cycle%203/Shift%20Reduce%20Parser/)

### Cycle 4
- [Intermediate Code Generation](./Cycle%204/Intermediate%20Code%20Generation/)

### Additional Questions
- Basic While Loop: [Lex](./Additional%20Questions/Basic%20While%20Loop/lexer.l) | [Yacc](./Additional%20Questions/Basic%20While%20Loop/parser.y)
- [Counter](./Additional%20Questions/Counter/)
- If-Else Ladder: [Lex](./Additional%20Questions/If-Else%20Ladder/lexer.l) | [Yacc](./Additional%20Questions/If-Else%20Ladder/parser.y)
- [Lexical Analyser](./Additional%20Questions/Lexical%20Analyser/)
- Nested While Loop: [Lex](./Additional%20Questions/Nested%20While%20Loop/lexer.l) | [Yacc](./Additional%20Questions/Nested%20While%20Loop/parser.y)
- [Replace Charecters](./Additional%20Questions/Replace%20Charecters/)

## Contributors

- [Niranjay Ajayan](https://github.com/dyingpotato890)
- [Vinay Chandrasekhar](https://github.com/vcgithub41210)