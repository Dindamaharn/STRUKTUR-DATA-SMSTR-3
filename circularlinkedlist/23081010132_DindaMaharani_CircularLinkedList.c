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
    node *pNew,*pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            *head = pNew;
            pNew->next =pNew;
        }else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next; 
            }
            pNew->next = *head;
            pCur->next = pNew;
            *head = pNew;
        }
        printf("Node dengan data %d berhasil ditambahkan di awal.\n", bil);
    } else {
        printf("Alokasi memori gagal\n");
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

    do {
        if (pCur->data == pos) break;
        pCur = pCur->next;
    } while (pCur != *head);  

    pNew = (node *)malloc(sizeof(node));

    if (pCur == *head && pCur->data != pos) { 
        printf("\nNode tidak ditemukan\n");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal\n");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
        printf("Node dengan data %d berhasil ditambahkan di tengah.\n", bil);
    }
    getch();
}

// ========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew;  
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next; 
            }
            pCur->next = pNew;
            pNew->next = *head;
        }
        printf("Node dengan data %d berhasil ditambahkan di akhir.\n", bil);
    } else {
        printf("Alokasi memori gagal\n");
        getch();
    }
}

// ========================================================

void cetakIsiList(node *head) {
    node *pWalker = head;
    system("cls");
    if (pWalker == NULL) {
        printf("List kosong.");
    } else {
        do {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->next;
        } while (pWalker != head);
        printf("(kembali ke head)\n");
    }
}

// ========================================================

void hapusAwal(node **head) {
    node *pTemp, *pCur;

    system("cls");
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    if ((*head)->next == *head) {  
        free(*head);
        *head = NULL;
    } else {
        pCur = *head;
        while (pCur->next != *head) {
            pCur = pCur->next;  
        }
        pTemp = *head;
        *head = (*head)->next;
        pCur->next = *head;  
        free(pTemp);
    }
    printf("Data di awal berhasil dihapus.\n");
    getch();
}

// ========================================================

void hapusTengah(node **head) {
    int val;
    node *pCur, *pPrev;
    pCur = *head;
    pPrev = NULL;

    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada data yang bisa dihapus.\n");
        return;
    }

    printf("Masukkan nilai yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &val);

    do {
        if (pCur->data == val) break;
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur == *head && pCur->data != val) {
        printf("\nNode dengan nilai %d tidak ditemukan.\n", val);
    } else {
        if (pPrev == NULL) {  
            if (pCur->next == *head) {
                *head = NULL;
            } else {
                node *pLast = *head;
                while (pLast->next != *head) {
                    pLast = pLast->next;
                }
                *head = pCur->next;
                pLast->next = *head;
            }
        } else {
            pPrev->next = pCur->next;
        }
        free(pCur);
        printf("\nNode dengan nilai %d berhasil dihapus.\n", val);
    }
    getch();
}

// ========================================================

void hapusAkhir(node **head) {
    node *pCur, *pPrev;
    pCur = *head;
    pPrev = NULL;
    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == *head) {  
        free(*head);
        *head = NULL;
    } else {
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;  
        free(pCur);
    }
    printf("Data di akhir berhasil dihapus.\n");
    getch();
}

// ========================================================

void cariData(node *head, int target) {
    int index = 0;
    node *pCur = head;
    
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }
    
    system("cls");
    do {
        if (pCur->data == target) {
            printf("Data %d ditemukan dalam linked list.\n", target);
            return;
        }
        pCur = pCur->next;
    } while (pCur != head);
    
    printf("Data %d tidak ditemukan.\n", target);
    getch();
}

// ========================================================

void jumlahData(node **head) {
    int count = 0;
    node *pCur = *head;

    if (*head == NULL) {
        printf("List kosong.\n");
        return;
    }

    system("cls");
    do {
        count++;
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Jumlah node di linked list: %d\n", count);
    getch();
}

// ========================================================

void totalData(node **head) {
    int sum = 0;
    node *pCur = *head;

    if (*head == NULL) {
        printf("List kosong.\n");
        return;
    }

    system("cls");
    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Jumlah seluruh data di linked list: %d\n", sum);
    getch();
}
