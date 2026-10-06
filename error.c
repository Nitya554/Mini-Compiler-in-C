#include <stdio.h>
#include "error.h"

void showError(const char message[])
{
    printf("\n[COMPILER ERROR] %s\n", message);
}

void showSyntaxError(const char message[])
{
    printf("\n[SYNTAX ERROR] %s\n", message);
}

void showSemanticError(const char message[])
{
    printf("\n[SEMANTIC ERROR] %s\n", message);
}

void showLexicalError(const char message[])
{
    printf("\n[LEXICAL ERROR] %s\n", message);
}