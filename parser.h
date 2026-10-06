#ifndef PARSER_H
#define PARSER_H

#define MAX_TOKENS 200

typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SYMBOL
} TokenType;

typedef struct {
    char value[20];
    TokenType type;
} Token;

int syntaxAnalysis(Token tokens[], int tokenCount);
int semanticAnalysis(Token tokens[], int tokenCount);

#endif