
#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1, i = 0;

void push(char ch)
{
    stack[++top] = ch;
}

void pop()
{
    top--;
}

int main()
{
    char x, ch;

    printf("Enter expression: ");
    scanf("%s", input);

    // Append $
    strcat(input, "$");

    // Initialize stack
    push('$');
    push('E');

    while (top >= 0)
    {
        x = stack[top];
        ch = input[i];

        // Accept
        if (x == '$' && ch == '$')
            break;

        // Terminal matching
        else if (x == ch)
        {
            pop();
            i++;
        }

        // E -> TQ
        else if (x == 'E')
        {
            if (ch == 'i' || ch == '(')
            {
                pop();
                push('Q');
                push('T');
            }
            else
                break;
        }

        // Q -> +TQ | #
        else if (x == 'Q')
        {
            pop();

            if (ch == '+')
            {
                push('Q');
                push('T');
                push('+');
            }
            else if (ch == ')' || ch == '$')
            {
                // Epsilon: push nothing
            }
            else
                break;
        }

        // T -> FR
        else if (x == 'T')
        {
            if (ch == 'i' || ch == '(')
            {
                pop();
                push('R');
                push('F');
            }
            else
                break;
        }

        // R -> *FR | #
        else if (x == 'R')
        {
            pop();

            if (ch == '*')
            {
                push('R');
                push('F');
                push('*');
            }
            else if (ch == '+' || ch == ')' || ch == '$')
            {
                // Epsilon: push nothing
            }
            else
                break;
        }

        // F -> (E) | i
        else if (x == 'F')
        {
            pop();

            if (ch == '(')
            {
                push(')');
                push('E');
                push('(');
            }
            else if (ch == 'i')
            {
                push('i');
            }
            else
                break;
        }

        else
            break;
    }

    if (top == 0 && stack[top] == '$' && input[i] == '$')
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}
