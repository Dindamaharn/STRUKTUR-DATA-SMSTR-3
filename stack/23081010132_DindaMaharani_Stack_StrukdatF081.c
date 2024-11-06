#include <stdio.h>
#include <stdlib.h> // Untuk system("cls")

// Definisi struktur Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Definisi struktur Stack
typedef struct Stack {
    int count;
    int maxSize;
    struct Node *top;
} Stack;

Stack stack; // Global stack

// Deklarasi fungsi
void createStack(int size);
int isFull();
int isEmpty();
void pushdata();
void popdata();
void stacktop();
void stackempty();
int stackfull(); // Mengembalikan boolean
int stackcount();
void destroystack();
void printStack();

int main() {
    int pilihan;
    int maxSize;

    printf("Masukkan ukuran maksimum stack: ");
    scanf("%d", &maxSize);
    createStack(maxSize);

    do {
        system("cls"); // Membersihkan layar
        printf("Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Stack Empty\n");
        printf("5. Stack Full\n");
        printf("6. Stack Count\n");
        printf("7. Destroy Stack\n");
        printf("8. Print Stack\n");
        printf("0. Exit\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            pushdata();
        } else if (pilihan == 2) {
            popdata();
        } else if (pilihan == 3) {
            stacktop();
        } else if (pilihan == 4) {
            stackempty();
        } else if (pilihan == 5) {
            stackfull();
        } else if (pilihan == 6) {
            stackcount();
        } else if (pilihan == 7) {
            destroystack();
        } else if (pilihan == 8) {
            printStack();
        } else if (pilihan == 0) {
            printf("Keluar dari program...\n");
        } else {
            printf("Input tidak valid!\n");
        }

        // Tunggu input untuk melanjutkan setelah setiap pilihan
        printf("Tekan Enter untuk melanjutkan...");
        getchar(); // Mengabaikan karakter newline yang tersisa di buffer
        getchar(); // Menunggu input dari pengguna

    } while (pilihan != 0);

    return 0;
}

// Membuat stack
void createStack(int size) {
    stack.maxSize = size;
    stack.top = NULL;
    stack.count = 0;
}

// Mengecek apakah stack penuh
int isFull() {
    return stack.count >= stack.maxSize;
}

// Mengecek apakah stack kosong
int isEmpty() {
    return stack.count == 0;
}

// Menambahkan data ke stack
void pushdata() {
    if (isFull()) {
        printf("Tidak dapat menambahkan data karena stack penuh.\n");
        return;
    }

    int data;
    printf("Masukkan data untuk di push ke dalam stack: ");
    scanf("%d", &data);

    Node *newNode = (Node *)malloc(sizeof(Node)); // Alokasi memori untuk node baru
    if (newNode == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }

    newNode->data = data; // Menyimpan data
    newNode->next = stack.top; // Menghubungkan node baru dengan top saat ini
    stack.top = newNode; // Memperbarui top
    stack.count++; // Increment count

    printf("Data %d berhasil ditambahkan ke dalam stack.\n", data);
}

// Menghapus data dari stack
void popdata() {
    if (isEmpty()) {
        printf("Tidak ada data yang bisa dihapus, karena stack kosong.\n");
        return;
    }

    Node *dltNode = stack.top; // Menyimpan node yang akan dihapus
    stack.top = stack.top->next; // Memperbarui top
    printf("Data %d berhasil dihapus dari stack.\n", dltNode->data);
    free(dltNode); // Menghapus node
    stack.count--; // Decrement count
}

// Menampilkan data paling atas (top)
void stacktop() {
    if (isEmpty()) {
        printf("Stack kosong.\n");
        return;
    }
    printf("Data paling atas: %d\n", stack.top->data);
}

// Menampilkan apakah stack kosong
void stackempty() {
    if (isEmpty()) {
        printf("Stack kosong.\n");
    } else {
        printf("Stack tidak kosong.\n");
    }
}

// Mengecek apakah stack penuh dan menampilkan status
int stackfull() {
    if (isFull()) {
        printf("Stack penuh.\n");
        return 1; // Mengembalikan true jika stack penuh
    } else {
        printf("Stack belum penuh.\n");
        return 0; // Mengembalikan false jika stack tidak penuh
    }
}

// Mengembalikan jumlah data dalam stack
int stackcount() {
    printf("Jumlah data dalam stack: %d\n", stack.count);
    return stack.count; // Mengembalikan nilai count
}

// Mengosongkan seluruh data dalam stack
void destroystack() {
    while (stack.top != NULL) {
        Node *temp = stack.top; // Menyimpan node yang akan dihapus
        stack.top = stack.top->next; // Memperbarui top
        free(temp); // Menghapus node
    }
    stack.count = 0; // Mengatur count menjadi 0
    printf("Seluruh data dalam stack berhasil dihapus.\n");
}

// Mencetak isi stack
void printStack() {
    if (isEmpty()) {
        printf("Stack kosong!\n");
        return;
    }

    Node *pwalker = stack.top; // Pointer untuk traversal
    printf("Isi data dalam stack (atas ke bawah): \n");
    while (pwalker != NULL) {
        printf("%d\n", pwalker->data); // Menampilkan data
        pwalker = pwalker->next; // Melanjutkan ke node berikutnya
    }
}
