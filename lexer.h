#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
typedef enum
{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_FLOAT_CONST,
    TOKEN_OPERATOR,
    TOKEN_SPECIAL_SYMBOL,
    TOKEN_STRING,
    TOKEN_CHARACTER,
    TOKEN_UNKNOWN
} TokenType;

//Function prototypes
// Perform lexical analysis on the input file
void analyze(FILE *fp);
//To Check whether word is keyword/identifier
int isKeyword(const char *word);
// Check whether a character can start an identifier
int isIdentifierStart(char ch);
// Check whether a character can be part of an identifier
int isIdentifierChar(char ch);
// Check whether a character is a Bracket
int isBracket(char ch);
// Check whether a character is a special symbol
int isSpecialSymbol(char ch);
// Check whether a character is an operator
int isOperatorStart(char ch);
// Print a token with its line number and token type
void printToken(int line,const char *lexeme, TokenType type);

#endif