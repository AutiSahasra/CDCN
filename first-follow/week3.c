
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char p[10][10], first[26][10], follow[26][10];
int n;

void add(char s[], char ch)
{
    int i;
    for(i = 0; s[i]; i++)
        if(s[i] == ch)
            return;

    s[i] = ch;
    s[i+1] = '\0';
}

void FIRST()
{
    int i, j, k, change = 1;

    while(change)
    {
        change = 0;

        for(i = 0; i < n; i++)
        {
            int A = p[i][0] - 'A';

            for(j = 3; p[i][j]; j++)
            {
                char ch = p[i][j];

                if(ch == '#')
                {
                    if(!strchr(first[A], '#'))
                    {
                        add(first[A], '#');
                        change = 1;
                    }
                    break;
                }

                if(!isupper(ch))
                {
                    if(!strchr(first[A], ch))
                    {
                        add(first[A], ch);
                        change = 1;
                    }
                    break;
                }

                int B = ch - 'A';

                for(k = 0; first[B][k]; k++)
                    if(first[B][k] != '#' &&
                       !strchr(first[A], first[B][k]))
                    {
                        add(first[A], first[B][k]);
                        change = 1;
                    }

                if(!strchr(first[B], '#'))
                    break;

                if(p[i][j+1] == '\0')
                {
                    if(!strchr(first[A], '#'))
                    {
                        add(first[A], '#');
                        change = 1;
                    }
                }
            }
        }
    }
}

void FOLLOW()
{
    int i, j, k, change = 1;

    add(follow[p[0][0]-'A'], '$');

    while(change)
    {
        change = 0;

        for(i = 0; i < n; i++)
        {
            int A = p[i][0] - 'A';

            for(j = 3; p[i][j]; j++)
            {
                if(isupper(p[i][j]))
                {
                    int B = p[i][j] - 'A';
                    int nullable = 1;

                    for(k = j+1; p[i][k]; k++)
                    {
                        char ch = p[i][k];

                        if(!isupper(ch))
                        {
                            if(!strchr(follow[B], ch))
                            {
                                add(follow[B], ch);
                                change = 1;
                            }
                            nullable = 0;
                            break;
                        }

                        int C = ch - 'A';

                        int x;
                        for(x = 0; first[C][x]; x++)
                            if(first[C][x] != '#' &&
                               !strchr(follow[B], first[C][x]))
                            {
                                add(follow[B], first[C][x]);
                                change = 1;
                            }

                        if(!strchr(first[C], '#'))
                        {
                            nullable = 0;
                            break;
                        }
                    }

                    if(nullable)
                    {
                        for(k = 0; follow[A][k]; k++)
                            if(!strchr(follow[B], follow[A][k]))
                            {
                                add(follow[B], follow[A][k]);
                                change = 1;
                            }
                    }
                }
            }
        }
    }
}

int main()
{
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E->TR):\n");

    for(i = 0; i < n; i++)
        scanf("%s", p[i]);

    FIRST();
    FOLLOW();

    printf("\nFIRST:\n");
    for(i = 0; i < n; i++)
        printf("FIRST(%c) = {%s}\n", p[i][0],
               first[p[i][0]-'A']);

    printf("\nFOLLOW:\n");
    for(i = 0; i < n; i++)
        printf("FOLLOW(%c) = {%s}\n", p[i][0],
               follow[p[i][0]-'A']);

    return 0;
}
