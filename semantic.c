#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semantic.h"
#include "symbol_table.h"

int semanticAnalysis(Token tokens[], int tokenCount)
{
    char variableName[50];
    char dataType[20];

    // ------------------------------------
    // Get variable name and data type
    // ------------------------------------

    strcpy(variableName, tokens[1].value);
    strcpy(dataType, tokens[0].value);

    // ------------------------------------
    // Check duplicate declaration
    // ------------------------------------

    if (findSymbol(variableName) != -1)
    {
        printf("\nSemantic Error: Variable '%s' is already declared.\n",
               variableName);

        return 0;
    }

    // ------------------------------------
    // Check identifiers
    // ------------------------------------

    for (int i = 3; i < tokenCount - 1; i++)
    {
        if (tokens[i].type == IDENTIFIER)
        {
            if (findSymbol(tokens[i].value) == -1)
            {
                printf("\nSemantic Error: Variable '%s' is not declared.\n",
                       tokens[i].value);

                return 0;
            }
        }
    }

    // ------------------------------------
    // Check division by zero
    // ------------------------------------

    for (int i = 3; i < tokenCount - 1; i++)
    {
        if (strcmp(tokens[i].value, "/") == 0)
        {
            if (i + 1 < tokenCount - 1 &&
                tokens[i + 1].type == NUMBER &&
                atof(tokens[i + 1].value) == 0)
            {
                printf("\nSemantic Error: Division by zero is not allowed.\n");

                return 0;
            }
        }
    }

    // ------------------------------------
    // INT type checking
    // ------------------------------------

    if (strcmp(dataType, "int") == 0)
    {
        for (int i = 3; i < tokenCount - 1; i++)
        {
            if (tokens[i].type == NUMBER &&
                strchr(tokens[i].value, '.') != NULL)
            {
                printf("\nSemantic Error: Decimal value '%s' cannot be assigned to int variable '%s'.\n",
                       tokens[i].value,
                       variableName);

                return 0;
            }
        }
    }

    // ------------------------------------
    // CHAR type checking
    // ------------------------------------

    if (strcmp(dataType, "char") == 0)
    {
        int operandCount = 0;

        for (int i = 3; i < tokenCount - 1; i++)
        {
            if (tokens[i].type == NUMBER ||
                tokens[i].type == IDENTIFIER)
            {
                operandCount++;
            }
        }

        /*
         * Our current lexer does not yet support
         * character literals such as 'A'.
         */

        if (operandCount > 0)
        {
            printf("\nSemantic Error: Character literals are not supported yet.\n");
            return 0;
        }
    }

    // ------------------------------------
    // Semantic analysis successful
    // ------------------------------------

    printf("\nSemantic Analysis: VALID\n");

    return 1;
}