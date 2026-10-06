#include <stdio.h>
#include <string.h>

#include "symbol_table.h"

Symbol symbolTable[MAX_SYMBOLS];

int symbolCount = 0;

// ------------------------------------
// Add symbol
// ------------------------------------

void addSymbol(char name[], char type[], char value[])
{
    // Check table capacity
    if (symbolCount >= MAX_SYMBOLS)
    {
        printf("\nSymbol Table Error: Table is full.\n");
        return;
    }

    // Check duplicate variable
    if (findSymbol(name) != -1)
    {
        printf("\nSymbol Table Error: '%s' already exists.\n",
               name);
        return;
    }

    // Store symbol information
    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    strcpy(symbolTable[symbolCount].value, value);

    symbolCount++;
}

// ------------------------------------
// Find symbol
// ------------------------------------

int findSymbol(char name[])
{
    for (int i = 0; i < symbolCount; i++)
    {
        if (strcmp(symbolTable[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

// ------------------------------------
// Display symbol table
// ------------------------------------

void displaySymbolTable()
{
    printf("\n============================================\n");
    printf("              SYMBOL TABLE\n");
    printf("============================================\n");

    printf("%-15s %-15s %-15s\n",
           "NAME",
           "TYPE",
           "VALUE");

    printf("--------------------------------------------\n");

    if (symbolCount == 0)
    {
        printf("No symbols found.\n");
        return;
    }

    for (int i = 0; i < symbolCount; i++)
    {
        printf("%-15s %-15s %-15s\n",
               symbolTable[i].name,
               symbolTable[i].type,
               symbolTable[i].value);
    }

    printf("============================================\n");
}