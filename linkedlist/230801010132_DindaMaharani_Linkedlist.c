#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
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

        if (pilih == '0') {
            tambahAwal(&head);
        } else if (pilih == '1') {
            tambahTengah(&head);
        } else if (pilih == '2') {
            tambahAkhir(&head);
        } else if (pilih == '3') {
            cetakIsiList(head);
            getch();
        } else if (pilih == '4') {
            hapusAwal(&head);
        } else if (pilih == '5') {
            hapusTengah(&head);
        } else if (pilih == '6') {
            hapusAkhir(&head);
        } else if (pilih == '7') {
            int target;
            printf("Masukkan nilai yang dicari: ");
            fflush(stdin);
            scanf("%d", &target);
            cariData(head, target);
            getch();
        } else if (pilih == '8') {
            jumlahData(&head);
        } else if (pilih == '9') {
            totalData(&head);
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
        pNew->next = *head;
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
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
        printf("Node dengan data %d berhasil ditambahkan di tengah. \n", bil);
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
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
            printf("Node dengan data %d berhasil ditambahakan sebagai node pertama. \n", bil);
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
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
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->next;
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
        *head = (*head)->next;
        free(pCur);
        printf("Data berhasil dihapus");
    }
    getch();
}

// ========================================================

void hapusTengah(node **head) {
    int val;
    node *pCur, *pPrev;
    pCur = *head;
    pPrev = NULL;
    
    printf("Masukkan nilai yang ingin dihapus: ");
    scanf("%d", &val);
    
    while (pCur != NULL && pCur->data != val) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Node dengan nilai %d tidak ditemukan.\n", val);
    } else {
        if (pPrev == NULL) {
            *head = pCur->next;
        } else {
            pPrev->next = pCur->next;
        }
        free(pCur);
        printf("Node dengan nilai %d berhasil dihapus.\n", val);
    }
}

// ========================================================

void hapusAkhir(node **head) {
    node *pCur, *pPrev;
    pCur = *head;
    pPrev = NULL;
    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    } else {
        while (pCur->next != NULL) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = NULL;
        free(pCur);
    }
    printf("Data di akhir berhasil dihapus.\n");
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
        pCur = pCur->next;
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
        pCur = pCur->next;
    }
    printf("Jumlah node di dalam linked list: %d", count);
    getch();
}

// ========================================================

void totalData(node **head) {
    int total = 0;
    node *pCur = *head;
    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }
    printf("Total penjumlahan seluruh data dalam list: %d", total);
    getch();
}