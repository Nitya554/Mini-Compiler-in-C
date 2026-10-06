#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "syntax.h"
#include "symbol_table.h"
#include "semantic.h"
#include "intermediate.h"
#include "optimizer.h"
#include "codegen.h"
#include "error.h"

int main()
{
    char input[500];

    Token tokens[MAX_TOKENS];

    int tokenCount;
    int statementsProcessed = 0;
int statementsAccepted = 0;
int statementsRejected = 0;

int syntaxErrors = 0;
int semanticErrors = 0;
    // ====================================
    // MINI COMPILER START
    // ====================================

    printf("====================================\n");
    printf("          MINI COMPILER\n");
    printf("====================================\n");

    printf("Enter code in ONE LINE (multiple statements allowed)\n");
    printf("Example: int a=5; int b=3; int result=a+b;\n\n");

    printf("> ");

    // ====================================
    // READ INPUT
    // ====================================

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("\nNo input received.\n");
        return 0;
    }

    // Remove newline
    input[strcspn(input, "\n")] = '\0';

    // ====================================
    // CHECK EMPTY INPUT
    // ====================================

    if (strlen(input) == 0)
    {
        showError("No input provided.");
        return 0;
    }

    // ====================================
    // CHECK WHETHER INPUT ENDS WITH ';'
    // ====================================

    int inputLength = strlen(input);

    // Remove trailing spaces
    while (inputLength > 0 &&
           isspace((unsigned char)input[inputLength - 1]))
    {
        input[inputLength - 1] = '\0';
        inputLength--;
    }

    int inputEndsWithSemicolon = 0;

    if (inputLength > 0 &&
        input[inputLength - 1] == ';')
    {
        inputEndsWithSemicolon = 1;
    }

    // ====================================
    // SPLIT INPUT BY ';'
    // ====================================

    char *stmt = strtok(input, ";");

    while (stmt != NULL)
    {
        char statement[100];

        // --------------------------------
        // Get next statement
        // --------------------------------

        char *nextStmt = strtok(NULL, ";");

        // --------------------------------
        // Copy current statement
        // --------------------------------

        strcpy(statement, stmt);

        /*
         * Add semicolon only when:
         *
         * 1. There is another statement after it
         *    OR
         *
         * 2. The original input actually ended
         *    with a semicolon.
         *
         * Therefore:
         *
         * int a=5;
         *       ↓
         * int a=5;
         *
         * But:
         *
         * int a=5
         *       ↓
         * int a=5
         */

        if (nextStmt != NULL || inputEndsWithSemicolon)
        {
            strcat(statement, ";");
        }

        printf("\nProcessing: %s\n", statement);

        // ====================================
        // PHASE 1: LEXICAL ANALYSIS
        // ====================================

        printf("\n========== LEXICAL ANALYSIS ==========\n");

        lexicalAnalysis(
            statement,
            tokens,
            &tokenCount
        );

        // ------------------------------------
        // Check lexical result
        // ------------------------------------

        if (tokenCount == 0)
        {
            showError("No valid tokens found.");

            printf("\nStatement rejected.\n");
            printf("------------------------------------\n");

            stmt = nextStmt;
            continue;
        }

        // ------------------------------------
        // Display tokens
        // ------------------------------------

        printTokens(tokens, tokenCount);

        // ====================================
        // PHASE 2: SYNTAX ANALYSIS
        // ====================================

        printf("\n========== SYNTAX ANALYSIS ==========\n");

        if (!syntaxAnalysis(tokens, tokenCount))
{
    syntaxErrors++;
    statementsRejected++;

    printf("\nStatement rejected.\n");
    printf("------------------------------------\n");

    stmt = nextStmt;
    continue;
}
        // ====================================
        // PHASE 3: SEMANTIC ANALYSIS
        // ====================================

        printf("\n========== SEMANTIC ANALYSIS ==========\n");

  if (!semanticAnalysis(tokens, tokenCount))
{
    semanticErrors++;
    statementsRejected++;

    printf("\nStatement rejected.\n");
    printf("------------------------------------\n");

    stmt = nextStmt;
    continue;
}

        // ====================================
        // PHASE 4: INTERMEDIATE CODE
        // ====================================

        printf("\n========== INTERMEDIATE CODE ==========\n");

        generateIntermediateCode(
            tokens,
            tokenCount
        );

        // ====================================
        // PHASE 5: CODE OPTIMIZATION
        // ====================================

        printf("\n========== CODE OPTIMIZATION ==========\n");

        optimizeTokens(
            tokens,
            tokenCount
        );

        // ====================================
        // PHASE 6: CODE GENERATION
        // ====================================

        printf("\n========== CODE GENERATION ==========\n");

        generateTargetCode(
            tokens,
            tokenCount
        );

        // ====================================
        // BUILD COMPLETE EXPRESSION
        // ====================================

        char expression[100] = "";

        for (int i = 3; i < tokenCount - 1; i++)
        {
            strcat(
                expression,
                tokens[i].value
            );

            if (i < tokenCount - 2)
            {
                strcat(expression, " ");
            }
        }

        // ====================================
        // ADD TO SYMBOL TABLE
        // ====================================

        addSymbol(
            tokens[1].value,
            tokens[0].value,
            expression
        );

        // ====================================
        // STATEMENT ACCEPTED
        // ====================================

        statementsAccepted++;

printf("\nStatement accepted.\n");
printf("------------------------------------\n");
        // Move to next statement
        stmt = nextStmt;
        statementsProcessed++;
    }

    // ====================================
    // FINAL SYMBOL TABLE
    // ====================================

    displaySymbolTable();

    // ====================================
    // COMPILATION FINISHED
    // ====================================

    printf("\n====================================\n");
    printf("       COMPILATION FINISHED\n");
    printf("====================================\n");

    // ====================================
// COMPILATION SUMMARY
// ====================================

printf("\n====================================\n");
printf("       COMPILATION SUMMARY\n");
printf("====================================\n");

printf("\nStatements processed : %d\n",
       statementsProcessed);

printf("Statements accepted  : %d\n",
       statementsAccepted);

printf("Statements rejected  : %d\n",
       statementsRejected);

printf("\nSyntax errors        : %d\n",
       syntaxErrors);

printf("Semantic errors      : %d\n",
       semanticErrors);

if (statementsRejected == 0)
{
    printf("\nCompilation Status   : SUCCESS\n");
}
else
{
    printf("\nCompilation Status   : FAILED\n");
}

printf("====================================\n");

return 0;
}