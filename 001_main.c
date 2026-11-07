/*
Description   :
Name          : Shaik Sharfuddin
Roll no       : 26012_016
Project Title : Lexical Analyzer
Start Date    : 17/09/2026
End Date      : 28/09/2026

Sample Output :
============================================================
                    LEXICAL ANALYZER
============================================================

LINE   LEXEME               TOKEN               
------------------------------------------------------------
1      #include <stdio.h>   -> PREPROCESSOR DIRECTIVE
2      #define MAX 100      -> PREPROCESSOR DIRECTIVE
3      //Comment            -> COMMENT
4      int                  -> KEYWORD
4      main                 -> IDENTIFIER
4      (                    -> BRACKET
4      )                    -> BRACKET
5      {                    -> BRACKET
6      ?                    -> LEXICAL ERROR
6      @                    -> LEXICAL ERROR
7      int                  -> KEYWORD
7      a                    -> IDENTIFIER
7      =                    -> OPERATOR
7      10                   -> INTEGER CONSTANT
7      ;                    -> SPECIAL SYMBOL
8      int                  -> KEYWORD
8      b                    -> IDENTIFIER
8      =                    -> OPERATOR
8      20                   -> INTEGER CONSTANT
8      @                    -> LEXICAL ERROR
8      ;                    -> SPECIAL SYMBOL
9      float                -> KEYWORD
9      x                    -> IDENTIFIER
9      =                    -> OPERATOR
9      10.25                -> FLOAT
9      ;                    -> SPECIAL SYMBOL
10     char                 -> KEYWORD
10     ch                   -> IDENTIFIER
10     =                    -> OPERATOR
10     'A'                  -> CHARACTER
10     ;                    -> SPECIAL SYMBOL
11     int                  -> KEYWORD
11     sum                  -> IDENTIFIER
11     =                    -> OPERATOR
11     a                    -> IDENTIFIER
11     +                    -> OPERATOR
11     b                    -> IDENTIFIER
11     ;                    -> SPECIAL SYMBOL
12     if                   -> KEYWORD
12     (                    -> BRACKET
12     sum                  -> IDENTIFIER
12     >=                   -> OPERATOR
12     30                   -> INTEGER CONSTANT
12     )                    -> BRACKET
12     {                    -> BRACKET
13     printf               -> IDENTIFIER
13     (                    -> BRACKET
13     "Sum is %d"          -> STRING
13     ,                    -> SPECIAL SYMBOL
13     sum                  -> IDENTIFIER
13     )                    -> BRACKET
13     ;                    -> SPECIAL SYMBOL
14     }                    -> BRACKET
15     return               -> KEYWORD
15     0                    -> INTEGER CONSTANT
15     ;                    -> SPECIAL SYMBOL
16     }                    -> BRACKET

==============================================================
                    ANALYSIS SUMMARY
==============================================================
Total Tokens        : 54
Keywords            : 8
Identifiers         : 11
Numbers             : 4
Floats              : 1
Operators           : 7
Brackets            : 10
Special Symbols     : 8
Strings             : 1
Characters          : 1
Comments            : 1
Preprocessors       : 2
Lexical Errors      : 3
==============================================================
                  LEXICAL ERRORS DETECTED
==============================================================

*/


#include <stdio.h>
#include "lexer.h"
int main()
{
    FILE *fp;
    //open "input.c in read mode"
    fp = fopen("input.c", "r");
    if (fp == NULL){
        printf("Error: Unable to open input.c\n");
        return 1;
    }
    //Printing Tokens/Lexens
    printf("============================================================\n");
    printf("                    LEXICAL ANALYZER\n");
    printf("============================================================\n\n");

    printf("%-6s %-20s %-20s\n", "LINE", "LEXEME", "TOKEN");
    printf("------------------------------------------------------------\n");
    // Start lexical analysis of the input source file
    analyze(fp);
    //Close the input file
    fclose(fp);
    return 0;
}