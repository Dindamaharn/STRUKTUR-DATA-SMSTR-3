#include <iostream>
#include <cstdlib> // Untuk system("cls")

using namespace std;

// Deklarasi fungsi terlebih dahulu
void createStack(int size);
bool isFull();
bool isEmpty();
void pushdata();
void popdata();
void stacktop();
void stackempty();
bool stackfull(); // Mengembalikan boolean
int stackcount();
void destroystack();
void printStack();

int main() {
    int pilihan;
    int maxSize;

    cout << "Masukkan ukuran maksimum stack: ";
    cin >> maxSize;
    createStack(maxSize);

    do {
        system("cls"); // Membersihkan layar
        cout << "Menu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Stack Empty\n";
        cout << "5. Stack Full\n";
        cout << "6. Stack Count\n";
        cout << "7. Destroy Stack\n";
        cout << "8. Print Stack\n";
        cout << "0. Exit\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

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
            cout << "Keluar dari program...\n";
        } else {
            cout << "Input tidak valid!\n";
        }

        // Tunggu input untuk melanjutkan setelah setiap pilihan
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    } while (pilihan != 0);

    return 0;
}

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

// Membuat stack
void createStack(int size) {
    stack.maxSize = size;
    stack.top = NULL;
    stack.count = 0;
}

// Mengecek apakah stack penuh
bool isFull() {
    return stack.count >= stack.maxSize;
}

// Mengecek apakah stack kosong
bool isEmpty() {
    return stack.count == 0;
}

// Menambahkan data ke stack
void pushdata() {
    if (isFull()) {
        cout << "Tidak dapat menambahkan data karena stack penuh.\n";
        return;
    }

    int data;
    cout << "Masukkan data untuk di push ke dalam stack: ";
    cin >> data;

    Node *newNode = new Node; // Alokasi memori untuk node baru
    if (newNode == NULL) {
        cout << "Alokasi memori gagal\n";
        return;
    }

    newNode->data = data; // Menyimpan data
    newNode->next = stack.top; // Menghubungkan node baru dengan top saat ini
    stack.top = newNode; // Memperbarui top
    stack.count++; // Increment count

    cout << "Data " << data << " berhasil ditambahkan ke dalam stack.\n";
}

// Menghapus data dari stack
void popdata() {
    if (isEmpty()) {
        cout << "Tidak ada data yang bisa dihapus, karena stack kosong.\n";
        return;
    }

    Node *dltNode = stack.top; // Menyimpan node yang akan dihapus
    stack.top = stack.top->next; // Memperbarui top
    cout << "Data " << dltNode->data << " berhasil dihapus dari stack.\n";
    delete dltNode; // Menghapus node
    stack.count--; // Decrement count
}

// Menampilkan data paling atas (top)
void stacktop() {
    if (isEmpty()) {
        cout << "Stack kosong.\n";
        return;
    }
    cout << "Data paling atas: " << stack.top->data << endl;
}

// Menampilkan apakah stack kosong
void stackempty() {
    if (isEmpty()) {
        cout << "Stack kosong.\n";
    } else {
        cout << "Stack tidak kosong.\n";
    }
}

// Mengecek apakah stack penuh dan menampilkan status
bool stackfull() {
    if (isFull()) {
        cout << "Stack penuh.\n";
        return true; // Mengembalikan true jika stack penuh
    } else {
        cout << "Stack belum penuh.\n";
        return false; // Mengembalikan false jika stack tidak penuh
    }
}

// Mengembalikan jumlah data dalam stack
int stackcount() {
    cout << "Jumlah data dalam stack: " << stack.count << endl;
    return stack.count; // Mengembalikan nilai count
}

// Mengosongkan seluruh data dalam stack
void destroystack() {
    while (stack.top != NULL) {
        Node *temp = stack.top; // Menyimpan node yang akan dihapus
        stack.top = stack.top->next; // Memperbarui top
        delete temp; // Menghapus node
    }
    stack.count = 0; // Mengatur count menjadi 0
    cout << "Seluruh data dalam stack berhasil dihapus.\n";
}

// Mencetak isi stack
void printStack() {
    if (isEmpty()) {
        cout << "Stack kosong!\n";
        return;
    }

    Node *pwalker = stack.top; // Pointer untuk traversal
    cout << "Isi data dalam stack (atas ke bawah): \n";
    while (pwalker != NULL) {
        cout << pwalker->data << endl; // Menampilkan data
        pwalker = pwalker->next; // Melanjutkan ke node berikutnya
    }
}
