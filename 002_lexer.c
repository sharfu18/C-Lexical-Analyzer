#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//Declare keywords
const char *keywords[] =
{
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

//Macro to count Keywords
#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

//check for keyword
int isKeyword(const char *word)
{
    for(int i = 0;i<KEYWORD_COUNT;i++){
        if(strcmp(word,keywords[i]) == 0){
            return TOKEN_KEYWORD;
        }
    }
    return TOKEN_UNKNOWN;
}

// Check identifier start
int isIdentifierStart(char ch)
{
    return isalpha((unsigned char)ch) || ch == '_';
}

// Check identifier character
int isIdentifierChar(char ch)
{
    return isalnum((unsigned char)ch) || ch == '_';
}

// Check special symbol
int isSpecialSymbol(char ch)
{
    if(ch == ';' || ch == ',' || ch == '.' || ch == ':'){
        return 1;
    }
    return 0;
}

//Check for bracket
int isBracket(char ch)
{
    if(ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']'){
        return 1;
    }
    return 0;
}

//check operator
int isOperatorStart(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '=' || ch == '<' ||
       ch == '>' || ch == '!' || ch == '&' || ch == '|'){
        return 1;
    }
    return 0;
}

//print token
void printToken(int line,const char *lexeme, TokenType type)
{
    switch(type){
        case TOKEN_KEYWORD:
        printf("%-6d %-20s -> KEYWORD\n",line,lexeme);
        break;
        case TOKEN_IDENTIFIER:
        printf("%-6d %-20s -> IDENTIFIER\n",line,lexeme);
        break;
        case TOKEN_CONSTANT:
        printf("%-6d %-20s -> INTEGER CONSTANT\n",line,lexeme);
        break;
        case TOKEN_FLOAT_CONST:
        printf("%-6d %-20s -> FLOAT\n",line,lexeme);
        break;
        case TOKEN_SPECIAL_SYMBOL:
        printf("%-6d %-20s -> SPECIAL SYMBOL\n", line,lexeme);
        break;
        case TOKEN_OPERATOR:
        printf("%-6d %-20s -> OPERATOR\n",line,lexeme);
        break;
        case TOKEN_STRING:
        printf("%-6d %-20s -> STRING\n",line,lexeme);
        break;
        case TOKEN_CHARACTER:
        printf("%-6d %-20s -> CHARACTER\n",line,lexeme);
        break;
        default:
        printf("%-6d %-20s -> UNKNOWN\n",line,lexeme);
    }
}

//perform lexical analysis
void analyze(FILE *fp)
{
    int ch;
    int line = 1;

    //Intialize counters
    int totalTokens = 0;
    int keywords = 0;
    int identifiers = 0;
    int numbers = 0;
    int floats = 0;
    int operators = 0;
    int brackets = 0;
    int specialSymbols = 0;
    int strings = 0;
    int characters = 0;
    int comments = 0;
    int preprocessors = 0;
    int lexicalErrors = 0;

    // Read file character by character
    while((ch = fgetc(fp)) != EOF){
         if(ch == '\n'){
            line++;
            continue;
        }
        if(ch == '\r'){
            continue;
        }
        //ignore spaces
        if(isspace((unsigned char)ch)){
            continue;
        }
        // check for preprocessor directive
        if(ch == '#')
        {
            char str[200];
            int idx = 0;
            str[idx++] = ch;
            while((ch = fgetc(fp)) != EOF && ch != '\n' && ch != '\r'){
                str[idx++] = ch;
            }
            str[idx] = '\0';
            printf("%-6d %-20s -> PREPROCESSOR DIRECTIVE\n",line,str);
            preprocessors++;
            totalTokens++;
            continue;
        }
        // Check for comments
        if(ch == '/')
        {
            int next = fgetc(fp);
            // Check for single-line comment
            if(next == '/'){
                char str[200];
                int idx = 0;
                str[idx++] = ch;
                str[idx++] = next;
                while((ch = fgetc(fp)) != EOF && ch != '\n' && ch != '\r'){
                    str[idx++] = ch;
                }
                str[idx] = '\0';
                printf("%-6d %-20s -> COMMENT\n", line, str);
                comments++;
                totalTokens++;
                continue;
            }
            // Check for multi-line comment
            else if(next == '*'){
                char str[500];
                int idx = 0;
                str[idx++] = ch;
                str[idx++] = next;
                while((ch = fgetc(fp)) != EOF){
                    str[idx++] = ch;
                    if(ch == '\n'){
                        line++;
                    }
                    if(ch == '*' ){
                        int end = fgetc(fp);
                        if(end == '/'){
                            str[idx++] = end;
                            break;
                        }
                        if(end != EOF){
                            ungetc(end, fp);
                        }
                    }
                }
                str[idx] = '\0';
                printf("%-6d %-20s -> COMMENT\n", line, str);
                comments++;
                totalTokens++;
                continue;
            }
            // '/' is an operator
            else{
                if(next != EOF){
                    ungetc(next, fp);
                }
            }
        }
        //Check for keyword/iderntifier
        if(isIdentifierStart((char)ch)){
            char str[100];
            int idx = 0;
            str[idx++] = ch;
            while((ch = fgetc(fp)) != EOF && isIdentifierChar((char)ch)){
                str[idx++] = ch;
            }
            str[idx] = '\0';
            if(isKeyword(str) == TOKEN_KEYWORD){
                printToken(line,str,TOKEN_KEYWORD);
                keywords++;
                totalTokens++;
            }
            else{
                printToken(line,str,TOKEN_IDENTIFIER); 
                identifiers++;
                totalTokens++;
            }
            if(ch != EOF){
            ungetc(ch,fp);
            }
            continue;
        }

        //Check for Integer constant and Float
        if(isdigit((unsigned char)ch)){
        char str[100];
        int idx = 0;
        int hasdot  = 0;
        str[idx++] = ch;
        while((ch = fgetc(fp)) != EOF){
            if(isdigit((unsigned char)ch)){
                str[idx++] = ch;
            }
            else if(ch == '.' && hasdot == 0){
                hasdot = 1;
                str[idx++] = ch;
            }
            else{
                break;
            }
        }

        // Check if a letter or underscore comes immediately after number
        if(ch != EOF && isIdentifierStart((char)ch)){
            str[idx++] = ch;
            while((ch = fgetc(fp)) != EOF && isIdentifierChar((char)ch)){
                str[idx++] = ch;
            }
            str[idx] = '\0';
            printf("%-6d %-20s -> LEXICAL ERROR\n",line, str);
            lexicalErrors++;
            if(ch != EOF){
                ungetc(ch, fp);
            }
            continue;
        }
        str[idx] = '\0';
        if(hasdot){
            printToken(line, str, TOKEN_FLOAT_CONST);
            floats++;
        }
        else{
            printToken(line, str, TOKEN_CONSTANT);
            numbers++;
        }
        totalTokens++;
        if(ch != EOF){
            ungetc(ch, fp);
        }
        continue;
    }
        //check for bracket
        if(isBracket((char)ch)){
            char str[2];
            str[0] = ch;
            str[1] = '\0';
            printf("%-6d %-20s -> BRACKET\n",line,str);
            brackets++;
            totalTokens++;
            continue;
        }
        //check for special symbol
        if(isSpecialSymbol((char)ch)){
            char str[2];
            str[0] = ch;
            str[1] = '\0';
            printToken(line,str, TOKEN_SPECIAL_SYMBOL);
            specialSymbols++;
            totalTokens++;
            continue;
        }
        //check for operator
        if(isOperatorStart((char)ch))
        {
            char str[3];
            int idx = 0;
            str[idx++] = ch;
            int next = fgetc(fp);
            if ((ch == '=' && next == '=') || (ch == '!' && next == '=') || (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') || (ch == '+' && next == '+') ||
                (ch == '-' && next == '-') || (ch == '&' && next == '&') || (ch == '|' && next == '|')){
                str[idx++] = next;
            }
            else{
                if (next != EOF){
                    ungetc(next, fp);
                }
            }
            str[idx] = '\0';
            printToken(line, str, TOKEN_OPERATOR);
            operators++;
            totalTokens++;
            continue;
        }
        //Check for string
        if(ch == '"'){
            char str[100];
            int idx = 0;
            str[idx++] = ch;
            while((ch = fgetc(fp)) != EOF){
                str[idx++] = ch;
                if(ch == '"'){
                    break;
                }
            }
            str[idx] = '\0';
            printToken(line,str,TOKEN_STRING);
            strings++;
            totalTokens++;
            continue;
        }
        //check for the character
        if(ch == '\''){
            char str[10];
            int idx = 0;
            str[idx++] = ch;
            while((ch = fgetc(fp)) != EOF){
                str[idx++] = ch;
                if(ch == '\''){
                    break;
                }
            }
            str[idx] = '\0';
            printToken(line,str,TOKEN_CHARACTER);
            characters++;
            totalTokens++;
            continue;
        }
        // Check for lexical error
        char str[2];
        str[0] = ch;
        str[1] = '\0';
        printf("%-6d %-20s -> LEXICAL ERROR\n", line, str);
        lexicalErrors++;
    }
    //Analysis Summary
    printf("\n==============================================================\n");
    printf("                    ANALYSIS SUMMARY\n");
    printf("==============================================================\n");

    printf("Total Tokens        : %d\n", totalTokens);
    printf("Keywords            : %d\n", keywords);
    printf("Identifiers         : %d\n", identifiers);
    printf("Numbers             : %d\n", numbers);
    printf("Floats              : %d\n", floats);
    printf("Operators           : %d\n", operators);
    printf("Brackets            : %d\n", brackets);
    printf("Special Symbols     : %d\n", specialSymbols);
    printf("Strings             : %d\n", strings);
    printf("Characters          : %d\n", characters);
    printf("Comments            : %d\n", comments);
    printf("Preprocessors       : %d\n", preprocessors);
    printf("Lexical Errors      : %d\n", lexicalErrors);
    if(lexicalErrors > 0){
    printf("\n==============================================================\n");
    printf("                  LEXICAL ERRORS DETECTED\n");
    printf("==============================================================\n");
    }
    else{
    printf("\n==============================================================\n");
    printf("                 NO LEXICAL ERRORS DETECTED\n");
    printf("==============================================================\n");
    }
}