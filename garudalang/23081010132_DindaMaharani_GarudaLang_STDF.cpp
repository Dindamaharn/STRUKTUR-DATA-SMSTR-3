#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  // Untuk tipe data bool

// Fungsi untuk memeriksa apakah kode valid
bool is_valid_code(const char* code) {
    // Stack untuk menyimpan tanda buka
    char stack[1000];
    int top = -1;  // Indeks untuk top stack
    
    // Iterasi melalui setiap karakter dalam kode
    for (int i = 0; code[i] != '\0'; i++) {
        char ch = code[i];
        
        // Jika karakter adalah tanda buka, push ke stack
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            stack[++top] = ch;  // Push ke stack
        }
        // Jika karakter adalah tanda tutup, periksa kecocokan dengan stack
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            // Jika stack kosong, berarti tidak ada tanda buka yang sesuai
            if (top == -1) {
                return false;
            }
            char topChar = stack[top--];  // Pop dari stack
            
            // Periksa apakah tanda buka yang ada di stack sesuai dengan tanda tutup yang ditemukan
            if ((ch == ')' && topChar != '(') || 
                (ch == '}' && topChar != '{') || 
                (ch == ']' && topChar != '[') ||
                (ch == '>' && topChar != '<')) {
                return false;
            }
        }
    }
    
    // Jika stack masih berisi elemen, berarti ada tanda buka yang tidak tertutup
    return top == -1;
}

int main() {
    char line[1000], allCode[10000] = "";
    char pilih;

    do {
        system("cls");  // Membersihkan layar di Windows

        printf("Masukkan kode untuk diperiksa validitasnya (tekan Enter 2 kali untuk selesai):\n");

        // Membaca input sampai pengguna menekan Enter dua kali
        while (1) {
            fgets(line, sizeof(line), stdin);

            // Berhenti jika input kosong (Enter ditekan dua kali)
            if (strcmp(line, "\n") == 0) {
                break;
            }

            // Tambahkan baris input ke semua kode
            strcat(allCode, line);
        }

        // Cek apakah kode valid atau tidak
        if (is_valid_code(allCode)) {
            printf("Kode valid!\n");
        } else {
            printf("Kode tidak valid!\n");
        }

        // Reset variabel allCode untuk input selanjutnya
        allCode[0] = '\0';

        printf("Tekan 0 untuk keluar, atau tekan tombol lain untuk memeriksa kode lain: ");
        scanf(" %c", &pilih);
        getchar();  // Membersihkan buffer

    } while (pilih != '0');

    return 0;
}
