
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char expression[100], op[100];
int top = -1;

struct Node
{
    char data;
    struct Node *left, *right;
};

struct Node* create(char ch)
{
    struct Node *n = malloc(sizeof(struct Node));
    n->data = ch;
    n->left = n->right = NULL;
    return n;
}

int prec(char ch)
{
    if(ch == '*' || ch == '/') return 2;
    if(ch == '+' || ch == '-') return 1;
    return 0;
}

// Construct AST
struct Node* build()
{
    struct Node *s[100];
    int t = -1;

    for(int i = 0; expression[i]; i++)
    {
        char ch = expression[i];

        if(isspace(ch)) continue;

        if(isalnum(ch))
            s[++t] = create(ch);

        else if(ch == '(')
            op[++top] = ch;

        else
        {
            while(top != -1 && op[top] != '(' &&
                  (ch == ')' || prec(op[top]) >= prec(ch)))
            {
                struct Node *n = create(op[top--]);
                n->right = s[t--];
                n->left = s[t--];
                s[++t] = n;
            }

            if(ch == ')') top--;
            else op[++top] = ch;
        }
    }

    while(top != -1)
    {
        struct Node *n = create(op[top--]);
        n->right = s[t--];
        n->left = s[t--];
        s[++t] = n;
    }

    return s[t];
}

// Display AST (Inorder)
void display(struct Node *root)
{
    struct Node *s[100], *cur = root;
    int t = -1;

    while(cur || t != -1)
    {
        while(cur)
        {
            s[++t] = cur;
            cur = cur->left;
        }

        cur = s[t--];
        printf("%c", cur->data);
        cur = cur->right;
    }
}

// Generate machine code (Postorder)
void generate(struct Node *root)
{
    struct Node *s1[100], *s2[100];
    int t1 = -1, t2 = -1;

    s1[++t1] = root;

    while(t1 != -1)
    {
        struct Node *n = s1[t1--];
        s2[++t2] = n;

        if(n->left) s1[++t1] = n->left;
        if(n->right) s1[++t1] = n->right;
    }

    while(t2 != -1)
    {
        struct Node *n = s2[t2--];

        if(!n->left)
            printf("PUSH %c\n", n->data);
        else
        {
            printf("POP R2\nPOP R1\n");

            if(n->data == '+') printf("ADD R1,R2\n");
            if(n->data == '-') printf("SUB R1,R2\n");
            if(n->data == '*') printf("MUL R1,R2\n");
            if(n->data == '/') printf("DIV R1,R2\n");

            printf("PUSH R1\n");
        }
    }

    printf("POP R1\nSTORE RESULT,R1\n");
}

int main()
{
    printf("Enter expression: ");
    fgets(expression, 100, stdin);

    struct Node *root = build();

    printf("\nAST: ");
    display(root);

    printf("\n\nMachine Code:\n");
    generate(root);

    return 0;
}
