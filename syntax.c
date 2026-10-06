#include <stdio.h>
#include <string.h>

#include "syntax.h"

int syntaxAnalysis(Token tokens[], int tokenCount)
{
    // ====================================
    // MINIMUM TOKEN CHECK
    // ====================================

    if (tokenCount < 4)
    {
        printf("\nSyntax Error: Incomplete statement.\n");
        return 0;
    }

    // ====================================
    // CHECK DATA TYPE
    // ====================================

    if (tokens[0].type != KEYWORD)
    {
        printf("\nSyntax Error: Data type is missing.\n");
        return 0;
    }

    if (strcmp(tokens[0].value, "int") != 0 &&
        strcmp(tokens[0].value, "float") != 0 &&
        strcmp(tokens[0].value, "char") != 0)
    {
        printf("\nSyntax Error: Unsupported data type '%s'.\n",
               tokens[0].value);
        return 0;
    }

    // ====================================
    // CHECK VARIABLE NAME
    // ====================================

    if (tokens[1].type != IDENTIFIER)
    {
        printf("\nSyntax Error: Variable name is missing.\n");
        return 0;
    }

    // ====================================
    // CHECK '='
    // ====================================

    if (strcmp(tokens[2].value, "=") != 0)
    {
        printf("\nSyntax Error: '=' is missing after variable '%s'.\n",
               tokens[1].value);
        return 0;
    }

    // ====================================
    // CHECK SEMICOLON
    // ====================================

    if (strcmp(tokens[tokenCount - 1].value, ";") != 0)
    {
        printf("\nSyntax Error: ';' is missing at the end of statement.\n");
        return 0;
    }

    // ====================================
    // CHECK EXPRESSION
    // ====================================

    int expectOperand = 1;
    int bracketCount = 0;

    for (int i = 3; i < tokenCount - 1; i++)
    {
        // =================================
        // EXPECTING VALUE / OPERAND
        // =================================

        if (expectOperand)
        {
            // Number
            if (tokens[i].type == NUMBER)
            {
                expectOperand = 0;
            }

            // Identifier
            else if (tokens[i].type == IDENTIFIER)
            {
                expectOperand = 0;
            }

            // Opening parenthesis
            else if (strcmp(tokens[i].value, "(") == 0)
            {
                bracketCount++;
            }

            // Operator found where value is expected
            else if (strcmp(tokens[i].value, "+") == 0 ||
                     strcmp(tokens[i].value, "-") == 0 ||
                     strcmp(tokens[i].value, "*") == 0 ||
                     strcmp(tokens[i].value, "/") == 0)
            {
                printf("\nSyntax Error: Value/operand is missing before '%s'.\n",
                       tokens[i].value);
                return 0;
            }

            else
            {
                printf("\nSyntax Error: Value/operand is missing.\n");
                return 0;
            }
        }

        // =================================
        // EXPECTING OPERATOR
        // =================================

        else
        {
            // Arithmetic operator
            if (strcmp(tokens[i].value, "+") == 0 ||
                strcmp(tokens[i].value, "-") == 0 ||
                strcmp(tokens[i].value, "*") == 0 ||
                strcmp(tokens[i].value, "/") == 0)
            {
                expectOperand = 1;
            }

            // Closing parenthesis
            else if (strcmp(tokens[i].value, ")") == 0)
            {
                if (bracketCount == 0)
                {
                    printf("\nSyntax Error: '(' is missing before ')'.\n");
                    return 0;
                }

                bracketCount--;
            }

            // Another value without operator
            else if (tokens[i].type == NUMBER ||
                     tokens[i].type == IDENTIFIER)
            {
                printf("\nSyntax Error: Operator is missing before '%s'.\n",
                       tokens[i].value);
                return 0;
            }

            else
            {
                printf("\nSyntax Error: Invalid expression near '%s'.\n",
                       tokens[i].value);
                return 0;
            }
        }
    }

    // ====================================
    // CHECK EXPRESSION END
    // ====================================

    if (expectOperand)
    {
        /*
         * Example:
         *
         * int a = 5+;
         */

        printf("\nSyntax Error: Value/operand is missing after operator.\n");
        return 0;
    }

    // ====================================
    // CHECK PARENTHESES
    // ====================================

    if (bracketCount != 0)
    {
        printf("\nSyntax Error: ')' is missing.\n");
        return 0;
    }

    // ====================================
    // SYNTAX SUCCESS
    // ====================================

    printf("\nSyntax Analysis: VALID\n");

    return 1;
}