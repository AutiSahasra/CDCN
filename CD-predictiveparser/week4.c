
#include <stdio.h>
#include <string.h>

char stack[100], input[100];

// Parsing table: rows = E,Q,T,R,F
// Columns = i,+,*,(,),$

char table[5][6][10] = {
    {"TQ",  "", "", "TQ", "", ""},
    {"", "+TQ", "", "", "#", "#"},
    {"FR", "", "", "FR", "", ""},
    {"", "#", "*FR", "", "#", "#"},
    {"i", "", "", "(E)", "", ""}
};

char nonterm[] = "EQTRF";
char terminal[] = "i+*()$";

int top = -1, i = 0;

void push(char ch)
{
    stack[++top] = ch;
}

void main()
{
    char x, ch;
    int row, col, j;

    printf("Enter expression: ");
    scanf("%s", input);

    strcat(input, "$");

    push('$');
    push('E');

    while (top >= 0)
    {
        x = stack[top];
        ch = input[i];

        if (x == '$' && ch == '$')
            break;

        // Terminal matching
        else if (x == ch)
        {
            top--;
            i++;
        }

        // Non-terminal: access parsing table
        else
        {
            for (row = 0; row < 5; row++)
                if (nonterm[row] == x)
                    break;

            for (col = 0; col < 6; col++)
                if (terminal[col] == ch)
                    break;

            if (row == 5 || col == 6 ||
                table[row][col][0] == '\0')
                break;

            char *prod = table[row][col];

            top--;

            // Epsilon
            if (strcmp(prod, "#") != 0)
            {
                for (j = strlen(prod) - 1; j >= 0; j--)
                    push(prod[j]);
            }
        }
    }

    if (top == 0 && stack[top] == '$' && input[i] == '$')
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");
}
