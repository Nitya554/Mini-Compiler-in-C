#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100

typedef struct
{
    char name[50];
    char type[20];
    char value[50];
} Symbol;

void addSymbol(char name[], char type[], char value[]);

int findSymbol(char name[]);

void displaySymbolTable();

#endif