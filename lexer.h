#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 50

typedef enum
{
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SYMBOL
} TokenType;

typedef struct
{
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

void lexicalAnalysis(char input[], Token tokens[], int *tokenCount);

void printTokens(Token tokens[], int tokenCount);

#endif