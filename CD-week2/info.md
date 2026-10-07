# Lexical Analyzer using Flex

## 1. Install WSL + Ubuntu

Open **PowerShell as Administrator**:

```bash
wsl --install -d Ubuntu
```

After Ubuntu opens, create your UNIX username and password:

```text
Enter new UNIX username: student
New password: <your-password>
```

---

## 2. Update Ubuntu

```bash
sudo apt update
```

Enter the password you created for Ubuntu when asked.

---

## 3. Install Required Tools

Install **Flex, GCC and Vim**:

```bash
sudo apt install flex gcc vim -y
```

Check that they are installed:

```bash
flex --version
gcc --version
vi --version
```

---

## 4. Create a Project Folder

Create a folder called `week2`:

```bash
mkdir week2
```

Go inside it:

```bash
cd week2
```

---

## 5. Create the Lex File

Create a file called `lexer.l`:

```bash
vi lexer.l
```

### Inside `vi`

Press:

```text
i
```

This enters **Insert Mode**.

Paste the following code:

```c
%{
#include <stdio.h>
%}

%%

"if"|"else"|"while"|"for"|"int"|"float"|"char"|"return" {
    printf("KEYWORD : %s\n", yytext);
}

[0-9]+ {
    printf("NUMBER : %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER : %s\n", yytext);
}

"=="|"!="|"<="|">="|"="|"+"|"-"|"*"|"/"|"<"|">" {
    printf("OPERATOR : %s\n", yytext);
}

"("|")"|"{"|"}"|";"|"," {
    printf("SPECIAL SYMBOL : %s\n", yytext);
}

[ \t\n]+ {
}

. {
    printf("UNKNOWN : %s\n", yytext);
}

%%

int main()
{
    printf("Enter the input:\n");
    yylex();
    return 0;
}
```

### Save and Exit `vi`

Press:

```text
Esc
```

Then type:

```text
:wq
```

Press **Enter**.

---

## 6. Check the File

Run:

```bash
ls
```

You should see:

```text
lexer.l
```

---

## 7. Generate C Code using Flex

Run:

```bash
lex lexer.l
```

This generates:

```text
lex.yy.c
```

Check:

```bash
ls
```

You should now see:

```text
lexer.l
lex.yy.c
```

---

## 8. Compile the Generated C Code

Run:

```bash
gcc lex.yy.c -ll
```

This creates an executable called:

```text
a.out
```

Check:

```bash
ls
```

You should see:

```text
a.out
lexer.l
lex.yy.c
```

---

## 9. Run the Lexical Analyzer

Run:

```bash
./a.out
```

You will see:

```text
Enter the input:
```

Now enter some C code.

Example:

```c
int a = 10;
if (a > 5)
    a = a + 1;
```

---

## 10. End the Input

After entering the input, press:

```text
Ctrl + D
```

`Ctrl + D` tells the program that the input has ended.

---

## 11. Expected Output

For:

```c
int a = 10;
if (a > 5)
    a = a + 1;
```

You will get output similar to:

```text
KEYWORD : int
IDENTIFIER : a
OPERATOR : =
NUMBER : 10
SPECIAL SYMBOL : ;
KEYWORD : if
SPECIAL SYMBOL : (
IDENTIFIER : a
OPERATOR : >
NUMBER : 5
SPECIAL SYMBOL : )
IDENTIFIER : a
OPERATOR : =
IDENTIFIER : a
OPERATOR : +
NUMBER : 1
SPECIAL SYMBOL : ;
```

---

# Complete Command Sequence

If everything is already installed, the normal workflow is:

```bash
mkdir week2
cd week2

vi lexer.l

lex lexer.l

gcc lex.yy.c -ll

./a.out
```

Then:

```text
Paste your input
        ↓
Press Ctrl + D
        ↓
See the lexical analyzer output
```

---

# `vi` Commands

| Key / Command | Purpose             |
| ------------- | ------------------- |
| `i`           | Enter Insert Mode   |
| `Esc`         | Exit Insert Mode    |
| `:wq`         | Save and Quit       |
| `Enter`       | Execute the command |

---

# Important Commands

```bash
# Create folder
mkdir week2

# Enter folder
cd week2

# Create/edit lex file
vi lexer.l

# Generate C file
lex lexer.l

# Compile
gcc lex.yy.c -ll

# Run
./a.out

# End input
Ctrl + D
```
