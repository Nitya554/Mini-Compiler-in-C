#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

int isKeyword(char word[])
{
    if (strcmp(word, "int") == 0 ||
        strcmp(word, "float") == 0 ||
        strcmp(word, "char") == 0)
    {
        return 1;
    }

    return 0;
}

void lexicalAnalysis(char input[], Token tokens[], int *tokenCount)
{
    int i = 0;

    *tokenCount = 0;

    while (input[i] != '\0')
    {
        // Ignore spaces
        if (isspace(input[i]))
        {
            i++;
            continue;
        }

        // Identifier or Keyword
        if (isalpha(input[i]))
        {
            char word[MAX_TOKEN_LENGTH];
            int j = 0;

            while (isalnum(input[i]))
            {
                word[j++] = input[i++];
            }

            word[j] = '\0';

            if (isKeyword(word))
            {
                tokens[*tokenCount].type = KEYWORD;
            }
            else
            {
                tokens[*tokenCount].type = IDENTIFIER;
            }

            strcpy(tokens[*tokenCount].value, word);

            (*tokenCount)++;
        }

        // Number
        // Number including decimal numbers
else if (isdigit(input[i]))
{
    char number[MAX_TOKEN_LENGTH];
    int j = 0;
    int decimalPoint = 0;

    while (isdigit(input[i]) || input[i] == '.')
    {
        if (input[i] == '.')
        {
            decimalPoint++;

            // More than one decimal point is invalid
            if (decimalPoint > 1)
            {
                break;
            }
        }

        number[j++] = input[i++];
    }

    number[j] = '\0';

    tokens[*tokenCount].type = NUMBER;

    strcpy(tokens[*tokenCount].value, number);

    (*tokenCount)++;
}

        // Operators
        else if (input[i] == '+' ||
                 input[i] == '-' ||
                 input[i] == '*' ||
                 input[i] == '/' ||
                 input[i] == '=')
        {
            tokens[*tokenCount].type = OPERATOR;

            tokens[*tokenCount].value[0] = input[i];
            tokens[*tokenCount].value[1] = '\0';

            (*tokenCount)++;

            i++;
        }

        // Symbols
        else if (input[i] == ';' ||
                 input[i] == '(' ||
                 input[i] == ')')
        {
            tokens[*tokenCount].type = SYMBOL;

            tokens[*tokenCount].value[0] = input[i];
            tokens[*tokenCount].value[1] = '\0';

            (*tokenCount)++;

            i++;
        }

        // Unknown character
        else
        {
            i++;
        }
    }
}

void printTokens(Token tokens[], int tokenCount)
{
    printf("\n--- TOKENS ---\n");

    for (int i = 0; i < tokenCount; i++)
    {
        printf("%s\t", tokens[i].value);

        switch (tokens[i].type)
        {
            case KEYWORD:
                printf("KEYWORD\n");
                break;

            case IDENTIFIER:
                printf("IDENTIFIER\n");
                break;

            case NUMBER:
                printf("NUMBER\n");
                break;

            case OPERATOR:
                printf("OPERATOR\n");
                break;

            case SYMBOL:
                printf("SYMBOL\n");
                break;
        }
    }
}