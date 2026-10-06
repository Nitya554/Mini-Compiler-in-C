#include <stdio.h>
#include <string.h>
#include "parser.h"

// Symbol Table
char symbolTable[50][20];
int symbolCount = 0;

int isDeclared(char *var)
{
    for (int i = 0; i < symbolCount; i++)
    {
        if (strcmp(symbolTable[i], var) == 0)
            return 1;
    }
    return 0;
}

void addSymbol(char *var)
{
    strcpy(symbolTable[symbolCount++], var);
}

int syntaxAnalysis(Token tokens[], int tokenCount)
{
    int start = 0;

    for (int i = 0; i < tokenCount; i++)
    {
        if (strcmp(tokens[i].value, ";") == 0)
        {
            if (tokens[start].type != KEYWORD)
            {
                printf("\nSyntax Error: Expected data type.\n");
                return 0;
            }

            if (tokens[start + 1].type != IDENTIFIER)
            {
                printf("\nSyntax Error: Expected identifier.\n");
                return 0;
            }

            if (strcmp(tokens[start + 2].value, "=") != 0)
            {
                printf("\nSyntax Error: Expected '='.\n");
                return 0;
            }

            for (int j = start + 3; j < i; j++)
            {
                if ((j - start) % 2 == 1)
                {
                    if (tokens[j].type != NUMBER &&
                        tokens[j].type != IDENTIFIER)
                    {
                        printf("\nSyntax Error: Expected operand.\n");
                        return 0;
                    }
                }
                else
                {
                    if (tokens[j].type != OPERATOR)
                    {
                        printf("\nSyntax Error: Expected operator.\n");
                        return 0;
                    }
                }
            }

            start = i + 1;
        }
    }

    printf("\nSyntax Analysis: VALID\n");
    return 1;
}

int semanticAnalysis(Token tokens[], int tokenCount)
{
    int start = 0;

    for (int i = 0; i < tokenCount; i++)
    {
        if (strcmp(tokens[i].value, ";") == 0)
        {
            char var[20];
            strcpy(var, tokens[start + 1].value);

            addSymbol(var);

            for (int j = start + 3; j < i; j++)
            {
                if (tokens[j].type == IDENTIFIER)
                {
                    if (!isDeclared(tokens[j].value))
                    {
                        printf("\nSemantic Error: Variable '%s' is not declared.\n", tokens[j].value);
                        return 0;
                    }
                }
            }

            start = i + 1;
        }
    }

    printf("\nSemantic Analysis: VALID\n");
    return 1;
}