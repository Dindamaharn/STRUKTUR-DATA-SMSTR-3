#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *right;
    struct node *left;
};

typedef struct node node;

void tambahAwal(node **head);
void tambahTengah(node **head);
void tambahAkhir(node **head);
void cetakIsiList(node *head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head, int val);
void jumlahData(node **head);
void totalData(node **head);

int main() {
    node *head = NULL;
    char pilih;
    int val;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("0. Tambah data di awal\n");
        printf("1. Tambah data di tengah list\n");
        printf("2. Tambah data di akhir linked list\n");
        printf("3. Cetak isi list\n");
        printf("4. Hapus data di awal linked list\n");
        printf("5. Hapus data di tengah linked list\n");
        printf("6. Hapus data di akhir linked list\n");
        printf("7. Pencarian data dalam linked list\n");
        printf("8. Menampilkan informasi jumlah data di linked list\n");
        printf("9. Menampilkan hasil penjumlahan dari semua data di linked list\n"); 
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf(" %c", &pilih);

        switch (pilih) {
            case '0': tambahAwal(&head); break;
            case '1': tambahTengah(&head); break;
            case '2': tambahAkhir(&head); break;
            case '3': cetakIsiList(head); getch(); break;
            case '4': hapusAwal(&head); break;
            case '5': hapusTengah(&head); break;
            case '6': hapusAkhir(&head); break;
            case '7': 
                printf("Masukkan nilai yang dicari: ");
                fflush(stdin);
                scanf("%d", &val);
                cariData(head, val); 
                getch(); 
                break;
            case '8': jumlahData(&head); break;
            case '9': totalData(&head); break;
        }

    } while (pilih != 'q');

    return 0;
}

// ========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->left = NULL;
        pNew->right = *head;

        if (*head != NULL) {
            (*head)->left = pNew;
        }

        *head = pNew;
        printf("Node dengan data %d berhasil ditambahkan di awal.\n", bil);
    } else {
        printf("Alokasi memori gagal.\n");
        getch();
    }
}

// ========================================================

void tambahTengah(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    cetakIsiList(*head);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->right;
    }

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
    } else {
        pNew = (node *)malloc(sizeof(node));
        if (pNew != NULL) {
            pNew->data = bil;
            pNew->left = pCur;
            pNew->right = pCur->right;

            if (pCur->right != NULL) {
                pCur->right->left = pNew;
            }
            pCur->right = pNew;
            printf("Node dengan data %d berhasil ditambahkan di tengah. \n", bil);
        } else {
            printf("\nAlokasi memori gagal");
        }
    }
    getch();
}

// ========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan sebuah bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    
    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->right = NULL;
        pNew->left = NULL;

        if (*head == NULL) {
            *head = pNew;
            printf("Node dengan data %d berhasil ditambahkan sebagai node pertama. \n", bil);
        } else {
            pCur = *head;
            while (pCur->right != NULL) {
                pCur = pCur->right;
            }
            pCur->right = pNew;
            pNew->left = pCur; // Set the left pointer of the new node
            printf("Node dengan data %d berhasil ditambahkan di akhir.\n", bil);
        }
    } else {
        printf("Alokasi memori gagal");
    }
    getch();
}

// ========================================================

void cetakIsiList(node *head) {
    node *pWalker = head;

    system("cls");

    if (pWalker == NULL) {
        printf("List kosong.");
    } else {
        while (pWalker != NULL) {
            printf("%d <-> ", pWalker->data);
            pWalker = pWalker->right;
        }
        printf("NULL");
    }
}

// ========================================================

void hapusAwal(node **head) {
    node *pCur;

    if (*head == NULL) {
        printf("List kosong\n");
    } else {
        pCur = *head;
        *head = (*head)->right;

        if (*head != NULL) {
            (*head)->left = NULL;
        }

        free(pCur);
        printf("Data berhasil dihapus");
    }
    getch();
}

// ========================================================

void hapusTengah(node **head) {
    int val;
    node *pCur;
    
    printf("Masukkan nilai yang ingin dihapus: ");
    scanf("%d", &val);

    pCur = *head;
    while (pCur != NULL && pCur->data != val) {
        pCur = pCur->right;
    }

    if (pCur == NULL) {
        printf("Node dengan nilai %d tidak ditemukan.\n", val);
    } else {
        if (pCur == *head) {
            hapusAwal(head);
        } else {
            if (pCur->right != NULL) {
                pCur->right->left = pCur->left;
            }
            if (pCur->left != NULL) {
                pCur->left->right = pCur->right;
            }
            free(pCur);
            printf("Node dengan nilai %d berhasil dihapus.\n", val);
        }
    }
}

// ========================================================

void hapusAkhir(node **head) {
    node *pCur;

    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->right == NULL) {
        free(*head);
        *head = NULL;
        printf("Node terakhir berhasil dihapus. List sekarang kosong.\n");
    } else {
        pCur = *head;
        while (pCur->right != NULL) {
            pCur = pCur->right;
        }

        pCur->left->right = NULL; // Set the right pointer of the previous node to NULL
        free(pCur);
        printf("Data di akhir berhasil dihapus.\n");
    }
    getch();
}

// ========================================================

void cariData(node *head, int target) {
    int index = 0;
    node *pCur = head;

    system("cls");
    
    while (pCur != NULL) {
        if (pCur->data == target) {
            printf("Data %d ditemukan pada index: %d\n", target, index);
            return;
        }
        pCur = pCur->right;
        index++;
    }
    printf("Data %d tidak ditemukan.\n", target);
    getch();
}

// ========================================================

void jumlahData(node **head) {
    int count = 0;
    node *pCur = *head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->right;
    }
    printf("Jumlah node di dalam linked list: %d\n", count);
    getch();
}

// ========================================================

void totalData(node **head) {
    int total = 0;
    node *pCur = *head;

    while (pCur != NULL) {
        total += pCur->data;
        pCur =pCur->right;
    }
    printf("Total penjumlahan seluruh data dalam list: %d", total);
    getch();
}
