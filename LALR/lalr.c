
#include <stdio.h>
#include <string.h>

char input[100];
int stack[100], top = 0, i = 0;

// ACTION columns: c,d,$
int action[7][3] = {
    { 3,  4,   0},
    { 0,  0, 999},
    { 3,  4,   0},
    { 3,  4,   0},
    {-3, -3,  -3},
    { 0,  0,  -1},
    {-2, -2,  -2}
};

// GOTO columns: S,C
int goTo[7][2] = {
    {1, 2},
    {0, 0},
    {0, 5},
    {0, 6},
    {0, 0},
    {0, 0},
    {0, 0}
};

// Production lengths
// 1: S -> CC
// 2: C -> cC
// 3: C -> d

int len[] = {0, 2, 2, 1};

// LHS mapping: S=0, C=1
int lhs[] = {-1, 0, 1, 1};

int getCol(char ch)
{
    char terminal[] = "cd$";
    int j;

    for(j = 0; j < 3; j++)
        if(terminal[j] == ch)
            return j;

    return -1;
}

int main()
{
    int state, col, act, p, g;
    int error = 0;

    printf("Enter string: ");
    scanf("%98s", input);

    strcat(input, "$");

    // Initial state
    stack[0] = 0;

    while(1)
    {
        state = stack[top];
        col = getCol(input[i]);

        if(col == -1)
        {
            error = 1;
            break;
        }

        act = action[state][col];

        // Accept
        if(act == 999)
            break;

        // Error
        else if(act == 0)
        {
            error = 1;
            break;
        }

        // Shift
        else if(act > 0)
        {
            stack[++top] = act;
            i++;
        }

        // Reduce
        else
        {
            p = -act;

            // Pop RHS length
            top = top - len[p];

            // Find GOTO state
            g = goTo[stack[top]][lhs[p]];

            if(g == 0)
            {
                error = 1;
                break;
            }

            // Push new state
            stack[++top] = g;
        }
    }

    if(!error && act == 999)
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}
