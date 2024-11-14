#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h> // untuk tipe boolean
#include <string.h> // Untuk strcspn

// Definisi node untuk stack
struct Node {
    char value;
    struct Node* next;
};

// Fungsi untuk membuat node baru
struct Node* newNode(char val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = val;
    node->next = NULL;
    return node;
}

// Struktur stack
struct Stack {
    struct Node* top;
};

// Fungsi untuk membuat stack kosong
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Fungsi untuk memeriksa apakah stack kosong
bool isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Fungsi untuk push elemen ke dalam stack
void push(struct Stack* stack, char value) {
    struct Node* new_node = newNode(value);
    new_node->next = stack->top;
    stack->top = new_node;
}

// Fungsi untuk pop elemen dari stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        struct Node* temp = stack->top;
        char poppedValue = temp->value;
        stack->top = stack->top->next;
        free(temp);
        return poppedValue;
    }
    return '\0';
}

// Fungsi untuk mengintip elemen teratas stack
char peek(struct Stack* stack) {
    return isEmpty(stack) ? '\0' : stack->top->value;
}

// Fungsi untuk menetapkan tingkat prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Fungsi untuk memeriksa keseimbangan tanda kurung
bool isBalanced(const char* expression) {
    struct Stack* stack = createStack();
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        if (ch == '(') {
            push(stack, ch);  // Menambah tanda kurung buka ke stack
        } else if (ch == ')') {
            if (isEmpty(stack)) {
                return false;  // Tidak ada kurung buka yang cocok
            }
            pop(stack);  // Menghapus tanda kurung buka yang cocok
        }
    }

    return isEmpty(stack);  // Jika stack kosong, berarti semua kurung telah seimbang
}

// Fungsi untuk mengonversi infix ke postfix
void infixToPostfix(const char* expression, char* output) {
    struct Stack* stack = createStack();
    int k = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        if (isalnum(ch)) { // Jika operand
            output[k++] = ch;
        } else if (ch == '(') {
            push(stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                output[k++] = pop(stack);
            }
            pop(stack); // Pop '('
        } else { // Operator
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(ch)) {
                output[k++] = pop(stack);
            }
            push(stack, ch);
        }
    }

    // Pop semua operator yang tersisa
    while (!isEmpty(stack)) {
        output[k++] = pop(stack);
    }
    output[k] = '\0';
    free(stack);
}

// Fungsi untuk mengevaluasi ekspresi postfix
int evaluatePostfix(const char* postfix) {
    struct Stack* stack = createStack();

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        
        if (isdigit(ch)) { // Jika operand
            push(stack, ch - '0');
        } else { // Operator
            int b = pop(stack);
            int a = pop(stack);
            switch (ch) {
                case '+': push(stack, a + b); break;
                case '-': push(stack, a - b); break;
                case '*': push(stack, a * b); break;
                case '/': push(stack, a / b); break;
            }
        }
    }

    int result = pop(stack);
    free(stack);
    return result;
}

int main() {
    char choice;
    char expression[100];
    bool exitProgram = false;

    do {
        printf("\nMenu:\n");
        printf("1. Konversi Infix ke Postfix\n");
        printf("2. Evaluasi Ekspresi Postfix\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf(" %c", &choice);
        getchar();  // Menghapus newline dari buffer

        if (choice == '1') {
            printf("Masukkan ekspresi infix: ");
            fgets(expression, sizeof(expression), stdin);

            // Menghapus newline dari fgets
            expression[strcspn(expression, "\n")] = '\0';

            // Pengecekan keseimbangan tanda kurung sebelum konversi
            if (!isBalanced(expression)) {
                printf("Ekspresi memiliki kesalahan dalam tanda kurung.\n");
            } else {
                char postfix[100];
                infixToPostfix(expression, postfix);
                printf("Ekspresi Postfix: %s\n", postfix);
            }
        } else if (choice == '2') {
            printf("Masukkan ekspresi postfix: ");
            fgets(expression, sizeof(expression), stdin);

            // Menghapus newline dari fgets
            expression[strcspn(expression, "\n")] = '\0';

            int result = evaluatePostfix(expression);
            printf("Hasil Evaluasi Postfix: %d\n", result);
        } else if (choice == '0') {
            exitProgram = true;
            printf("Keluar dari program.\n");
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

    } while (!exitProgram);

    return 0;
}
