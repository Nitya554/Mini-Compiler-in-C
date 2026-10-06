#include <stdio.h>
#include <string.h>

#include "codegen.h"

int targetTempCount = 1;

int isCodegenOperator(char value[])
{
    return strcmp(value, "+") == 0 ||
           strcmp(value, "-") == 0 ||
           strcmp(value, "*") == 0 ||
           strcmp(value, "/") == 0;
}

int codegenPrecedence(char value[])
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

void generateOperation(char operands[][50],
                       int *operandCount,
                       char operators[][10],
                       int *operatorCount)
{
    char temp[50];

    sprintf(temp, "R%d", targetTempCount++);

    printf("MOV %s, %s\n",
           temp,
           operands[*operandCount - 2]);

    printf("MOV R%d, %s\n",
           targetTempCount,
           operands[*operandCount - 1]);

    if (strcmp(
            operators[*operatorCount - 1],
            "+") == 0)
    {
        printf("ADD %s, R%d\n",
               temp,
               targetTempCount);
    }
    else if (strcmp(
                 operators[*operatorCount - 1],
                 "-") == 0)
    {
        printf("SUB %s, R%d\n",
               temp,
               targetTempCount);
    }
    else if (strcmp(
                 operators[*operatorCount - 1],
                 "*") == 0)
    {
        printf("MUL %s, R%d\n",
               temp,
               targetTempCount);
    }
    else if (strcmp(
                 operators[*operatorCount - 1],
                 "/") == 0)
    {
        printf("DIV %s, R%d\n",
               temp,
               targetTempCount);
    }

    targetTempCount++;

    strcpy(operands[*operandCount - 2], temp);

    (*operandCount)--;
    (*operatorCount)--;
}

void generateTargetCode(Token tokens[], int tokenCount)
{
    printf("\n--- TARGET CODE ---\n");

    // ------------------------------------
    // Simple assignment
    // ------------------------------------

    if (tokenCount == 5)
    {
        printf("MOV R1, %s\n",
               tokens[3].value);

        printf("MOV %s, R1\n",
               tokens[1].value);

        return;
    }

    char operands[100][50];
    char operators[100][10];

    int operandCount = 0;
    int operatorCount = 0;

    // ------------------------------------
    // Read expression
    // ------------------------------------

    for (int i = 3; i < tokenCount - 1; i++)
    {
        if (tokens[i].type == NUMBER ||
            tokens[i].type == IDENTIFIER)
        {
            strcpy(operands[operandCount],
                   tokens[i].value);

            operandCount++;
        }

        else if (strcmp(tokens[i].value, "(") == 0)
        {
            strcpy(operators[operatorCount],
                   "(");

            operatorCount++;
        }

        else if (strcmp(tokens[i].value, ")") == 0)
        {
            while (operatorCount > 0 &&
                   strcmp(
                       operators[operatorCount - 1],
                       "(") != 0)
            {
                generateOperation(
                    operands,
                    &operandCount,
                    operators,
                    &operatorCount
                );
            }

            if (operatorCount > 0)
            {
                operatorCount--;
            }
        }

        else if (isCodegenOperator(tokens[i].value))
        {
            while (operatorCount > 0 &&
                   strcmp(
                       operators[operatorCount - 1],
                       "(") != 0 &&
                   codegenPrecedence(
                       operators[operatorCount - 1])
                   >= codegenPrecedence(
                       tokens[i].value))
            {
                generateOperation(
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

    // ------------------------------------
    // Process remaining operators
    // ------------------------------------

    while (operatorCount > 0)
    {
        generateOperation(
            operands,
            &operandCount,
            operators,
            &operatorCount
        );
    }

    // ------------------------------------
    // Final assignment
    // ------------------------------------

    if (operandCount > 0)
    {
        printf("MOV %s, %s\n",
               tokens[1].value,
               operands[0]);
    }
}