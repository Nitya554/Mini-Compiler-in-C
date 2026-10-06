#include <stdio.h>
#include <string.h>

#include "intermediate.h"

int tempCount = 1;

/* Check whether token is an arithmetic operator */
int isOperator(char value[])
{
    return strcmp(value, "+") == 0 ||
           strcmp(value, "-") == 0 ||
           strcmp(value, "*") == 0 ||
           strcmp(value, "/") == 0;
}

/* Operator precedence */
int precedence(char value[])
{
    if (strcmp(value, "+") == 0 ||
        strcmp(value, "-") == 0)
    {
        return 1;
    }

    if (strcmp(value, "*") == 0 ||
        strcmp(value, "/") == 0)
    {
        return 2;
    }

    return 0;
}

/* Generate one temporary operation */
void createTemporary(char operands[][50],
                     int *operandCount,
                     char operators[][10],
                     int *operatorCount)
{
    char temp[50];

    sprintf(temp, "t%d", tempCount++);

    printf("%s = %s %s %s\n",
           temp,
           operands[*operandCount - 2],
           operators[*operatorCount - 1],
           operands[*operandCount - 1]);

    /* Replace two operands with one temporary */
    strcpy(operands[*operandCount - 2], temp);

    (*operandCount)--;

    (*operatorCount)--;
}

void generateIntermediateCode(Token tokens[], int tokenCount)
{
    printf("\n--- THREE ADDRESS CODE ---\n");

    /*
     * Simple assignment:
     *
     * int x = 10;
     */

    if (tokenCount == 5)
    {
        printf("%s = %s\n",
               tokens[1].value,
               tokens[3].value);

        return;
    }

    char operands[100][50];
    char operators[100][10];

    int operandCount = 0;
    int operatorCount = 0;

    /*
     * Scan the expression from left to right.
     */

    for (int i = 3; i < tokenCount - 1; i++)
    {
        /* Operand */
        if (tokens[i].type == NUMBER ||
            tokens[i].type == IDENTIFIER)
        {
            strcpy(operands[operandCount],
                   tokens[i].value);

            operandCount++;
        }

        /* Opening parenthesis */
        else if (strcmp(tokens[i].value, "(") == 0)
        {
            strcpy(operators[operatorCount], "(");

            operatorCount++;
        }

        /* Closing parenthesis */
        else if (strcmp(tokens[i].value, ")") == 0)
        {
            while (operatorCount > 0 &&
                   strcmp(operators[operatorCount - 1], "(") != 0)
            {
                createTemporary(
                    operands,
                    &operandCount,
                    operators,
                    &operatorCount
                );
            }

            /* Remove '(' */
            if (operatorCount > 0)
            {
                operatorCount--;
            }
        }

        /* Arithmetic operator */
        else if (isOperator(tokens[i].value))
        {
            while (operatorCount > 0 &&
                   strcmp(operators[operatorCount - 1], "(") != 0 &&
                   precedence(operators[operatorCount - 1])
                   >= precedence(tokens[i].value))
            {
                createTemporary(
                    operands,
                    &operandCount,
                    operators,
                    &operatorCount
                );
            }

            strcpy(operators[operatorCount],
                   tokens[i].value);

            operatorCount++;
        }
    }

    /* Process remaining operators */
    while (operatorCount > 0)
    {
        createTemporary(
            operands,
            &operandCount,
            operators,
            &operatorCount
        );
    }

    /* Final assignment */
    if (operandCount > 0)
    {
        printf("%s = %s\n",
               tokens[1].value,
               operands[0]);
    }
}