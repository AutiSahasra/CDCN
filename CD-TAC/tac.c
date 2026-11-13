
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char operands[100][100]; //otop
char operators[100];//atop

int otop = -1, atop = -1;
int temp = 1;

// Operator precedence
int precedence(char op)
{
    if(op == '*' || op == '/')
        return 2;

    if(op == '+' || op == '-')
        return 1;

    return 0;
}

// Generate TAC for the top operator
void generate()
{
    char a[100], b[100], t[100];
    char op;

    strcpy(b, operands[otop--]);
    strcpy(a, operands[otop--]);

    op = operators[atop--];

    sprintf(t, "t%d", temp++);

    printf("%s = %s %c %s\n", t, a, op, b);

    strcpy(operands[++otop], t);
}

int main()
{
    char input[100];
    int i = 0;

    printf("Enter arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    printf("\nThree Address Code:\n");

    while(input[i] != '\0' && input[i] != '\n')
    {
        // Skip spaces
        if(input[i] == ' ')
        {
            i++;
        }

        // Read operand (variable or number)
        else if(isalnum(input[i]) || input[i] == '_')
        {
            char token[100];
            int j = 0;

            while(isalnum(input[i]) || input[i] == '_')
                token[j++] = input[i++];

            token[j] = '\0';

            strcpy(operands[++otop], token);
        }

        // Opening parenthesis
        else if(input[i] == '(')
        {
            operators[++atop] = input[i++];
        }

        // Closing parenthesis
        else if(input[i] == ')')
        {
            while(atop >= 0 && operators[atop] != '(')
                generate();

            atop--;  // Remove '('
            i++;
        }

        // Operators: +, -, *, /
        else
        {
            while(atop >= 0 &&
                  operators[atop] != '(' &&
                  precedence(operators[atop]) >= precedence(input[i]))
            {
                generate();
            }

            operators[++atop] = input[i++];
        }
    }

    // Process remaining operators
    while(atop >= 0)
        generate();

    return 0;
}
