#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>  // Tambahkan pustaka ini untuk menggunakan tipe bool

//========================================================

typedef struct node {
    int data; 
    struct node *next;
} node;

typedef struct Stack {
    int count;
    node *top;
} Stack;

Stack stack;

//========================================================

void createStack();   
void push(int ch);   
void pop();              
int stackTop();       
bool emptyStack();      // Menggunakan bool di sini
int precedence(char op);
int isOperand(char ch);
int isValidExpression(const char* exp);
char* infixToPostfix(const char *exp);
int evaluatePostfix(const char *exp);

//========================================================

int main() {
    char infixExp[100];

    createStack();

    printf("Masukkan ekspresi infix: ");
    fgets(infixExp, sizeof(infixExp), stdin);
    infixExp[strcspn(infixExp, "\n")] = '\0'; // Menghapus karakter newline

    if (!isValidExpression(infixExp)) {
        printf("Ekspresi tidak valid.\n");
        return 0;
    }

    // Konversi infix ke postfix
    char* postfixExp = infixToPostfix(infixExp);
    printf("Ekspresi dalam bentuk postfix: %s\n", postfixExp);

    // Evaluasi postfix
    int result = evaluatePostfix(postfixExp);
    printf("Hasil evaluasi ekspresi postfix: %d\n", result);

    free(postfixExp); // Bebaskan memori yang dialokasikan untuk postfixExp

    return 0;
}

//========================================================

// Fungsi untuk membuat stack baru
void createStack() {
    stack.count = 0;
    stack.top = NULL;
}

int isOperand(char ch) {
    return isdigit(ch);
}

// Fungsi untuk menentukan presedensi hirarki operator
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    }
    return 0;
}

// Fungsi untuk memeriksa apakah ekspresi infix benar
int isValidExpression(const char* exp) {
    createStack();  

    for (int i = 0; exp[i] != '\0'; i++) {
        char ch = exp[i];
        if (ch == '(') {
            push('(');  
        } else if (ch == ')') {
            if (emptyStack()) {
                return 0; 
            }
            pop(); 
        }
    }
    return emptyStack(); 
}

// Fungsi untuk mengubah infix ke postfix
char* infixToPostfix(const char *exp) {
    createStack();
    char* postfix = (char*)malloc(100 * sizeof(char)); // Alokasi memori untuk hasil postfix
    strcpy(postfix, "");
    char currentNum[10] = ""; // Untuk menangani angka multi-digit

    for (int i = 0; exp[i] != '\0'; i++) {
        char ch = exp[i];

        // Abaikan spasi
        if (ch == ' ') continue;

        if (isdigit(ch)) {
            int len = strlen(currentNum);
            currentNum[len] = ch;
            currentNum[len + 1] = '\0'; // Tambahkan ke currentNum
        } else {

            if (strlen(currentNum) > 0) {
                strcat(postfix, currentNum);
                strcat(postfix, " ");
                currentNum[0] = '\0'; // Kosongkan currentNum
            }

            if (ch == '(') {
                push(ch);
            } else if (ch == ')') {
                while (!emptyStack() && stackTop() != '(') {
                    char temp[2] = {stackTop(), '\0'};
                    strcat(postfix, temp);
                    strcat(postfix, " ");
                    pop();
                }
                pop(); 
            } else { // Jika karakter adalah operator
                while (!emptyStack() && precedence(stackTop()) >= precedence(ch)) {
                    char temp[2] = {stackTop(), '\0'};
                    strcat(postfix, temp);
                    strcat(postfix, " ");
                    pop();
                }
                push(ch);
            }
        }
    }

    if (strlen(currentNum) > 0) {
        strcat(postfix, currentNum);
        strcat(postfix, " ");
    }

    // Mengosongkan stack yang tersisa
    while (!emptyStack()) {
        char temp[2] = {stackTop(), '\0'};
        strcat(postfix, temp);
        strcat(postfix, " ");
        pop();
    }

    return postfix;
}

int evaluatePostfix(const char *exp) {
    createStack();  
    char *token = strtok((char*)exp, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            push(atoi(token)); 
        } else {
            int operand2 = stackTop();
            pop();
            int operand1 = stackTop();
            pop();

            switch (token[0]) {
                case '+': push(operand1 + operand2); break;
                case '-': push(operand1 - operand2); break;
                case '*': push(operand1 * operand2); break;
                case '/': push(operand1 / operand2); break;
                case '^': push((int)pow(operand1, operand2)); break;
            }
        }
        token = strtok(NULL, " ");
    }

    return stackTop();
}

// Fungsi untuk memasukkan data ke dalam stack
void push(int ch) {
    node *pNew = (node*)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = ch;
        pNew->next = stack.top;
        stack.top = pNew;
        stack.count++;
    }
}

// Fungsi untuk mengeluarkan data dari stack
void pop() {
    if (!emptyStack()) {
        node *dltPtr = stack.top;
        stack.top = stack.top->next;
        stack.count--;
        free(dltPtr);
    }
}

// Fungsi untuk melihat data paling atas dalam stack
int stackTop() {
    if (!emptyStack()) {
        return stack.top->data;
    }
    return 0; 
}

// Fungsi untuk mengecek apakah stack kosong
bool emptyStack() {
    return stack.count == 0;
}
