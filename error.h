#ifndef ERROR_H
#define ERROR_H

void showError(const char message[]);

void showSyntaxError(const char message[]);

void showSemanticError(const char message[]);

void showLexicalError(const char message[]);

#endif