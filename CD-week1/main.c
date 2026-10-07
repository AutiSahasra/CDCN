#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void"
};

int isKeyword(char str[]) {
    int i;

    for (i = 0; i < 9; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main() {
    FILE *fp;
    int ch;
    char buffer[32];
    int i;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore spaces [1]
        if (isspace(ch))
            continue;

        // Comments or division operator [2]
        if (ch == '/') {
            int next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            }

            // Multi-line comment
            else if (next == '*') {
                int prev = 0;

                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;

                    prev = ch;
                }
            }

            // Division operator
            else {
                printf("Operator   : /\n");

                if (next != EOF)
                    fseek(fp, -1, SEEK_CUR);
            }
        }

        // Keyword or Identifier [3]
        else if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {

                if (i < 31)
                    buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            if (isKeyword(buffer))
                printf("Keyword    : %s\n", buffer);
            else
                printf("Identifier : %s\n", buffer);
        }

        // Number [4]
        else if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && isdigit(ch)) {
                if (i < 31)
                    buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            printf("Number     : %s\n", buffer);
        }

        // Operators
        else if (strchr("+-*=<>!", ch)) {
            int next = fgetc(fp);

            // Two-character operators
            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=')) {

                printf("Operator   : %c%c\n", ch, next);
            }
            else {
                printf("Operator   : %c\n", ch);

                if (next != EOF)
                    fseek(fp, -1, SEEK_CUR);
            }
        }

        // Delimiters
        else if (strchr("(){}[],;", ch)) {
            printf("Delimiter  : %c\n", ch);
        }

        // Invalid character
        else {
            printf("Invalid Character : %c\n", ch);
        }
    }

    fclose(fp);

    return 0;
}