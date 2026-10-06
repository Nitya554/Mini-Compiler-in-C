#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optimizer.h"

void optimizeTokens(Token tokens[], int tokenCount)
{
    printf("\n--- CODE OPTIMIZATION ---\n");

    /*
     * Constant Folding
     *
     * Example:
     *
     * int x = 10 + 20;
     *
     * Before:
     * 10 + 20
     *
     * After:
     * 30
     */

    int changed = 0;

    // ------------------------------------
    // Look for constant operations
    // ------------------------------------

    for (int i = 3; i < tokenCount - 1; i++)
    {
        if (tokens[i].type == NUMBER &&
            i + 2 < tokenCount &&
            tokens[i + 1].type == OPERATOR &&
            tokens[i + 2].type == NUMBER)
        {
            double left = atof(tokens[i].value);
            double right = atof(tokens[i + 2].value);

            double result = 0;

            char operator = tokens[i + 1].value[0];

            // --------------------------------
            // Perform operation
            // --------------------------------

            if (operator == '+')
            {
                result = left + right;
            }
            else if (operator == '-')
            {
                result = left - right;
            }
            else if (operator == '*')
            {
                result = left * right;
            }
            else if (operator == '/')
            {
                if (right == 0)
                {
                    printf("Optimization skipped: Division by zero.\n");
                    continue;
                }

                result = left / right;
            }
            else
            {
                continue;
            }

            printf("Constant Folding:\n");

            printf("Before: %s %c %s\n",
                   tokens[i].value,
                   operator,
                   tokens[i + 2].value);

            // --------------------------------
            // Display result
            // --------------------------------

            if (result == (int)result)
            {
                printf("After:  %d\n",
                       (int)result);
            }
            else
            {
                printf("After:  %.2f\n",
                       result);
            }

            changed = 1;
        }
    }

    // ------------------------------------
    // No optimization
    // ------------------------------------

    if (!changed)
    {
        printf("No constant folding possible.\n");
    }
}