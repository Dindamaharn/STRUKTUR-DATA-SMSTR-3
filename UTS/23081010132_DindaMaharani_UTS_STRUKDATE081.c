#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Struktur data node untuk menyimpan mahasiswa
struct node {
    char nama[100];     
    char jenis_kelamin;
    struct node *next;
};

// Fungsi-fungsi yang digunakan
void tambahMahasiswa(struct node **head);
void keluarLingkaran(struct node **head);
void pisahkanLingkaran(struct node *head);
void cetakIsiList(struct node *head);  // Fungsi untuk mencetak isi list

// Variabel global untuk lingkaran pria dan wanita
struct node *headPria = NULL;
struct node *headWanita = NULL;

int main() {
    struct node *head = NULL;
    int pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("1. Tambah mahasiswa\n");
        printf("2. Keluar dari lingkaran\n");
        printf("3. Cetak isi list\n");
        printf("4. Pisahkan lingkaran\n");
        printf("0. Keluar program\n");

        printf("MASUKKAN PILIHAN: ");
        fflush(stdin);
        scanf("%d", &pilih);

        if (pilih == 1) {
            tambahMahasiswa(&head);
        } else if (pilih == 2) {
            keluarLingkaran(&head);
        } else if (pilih == 3) {
            cetakIsiList(head);
            getch();
        } else if (pilih == 4) {
            pisahkanLingkaran(head);
        } else if (pilih == 0) {
            printf("Keluar dari program.\n");
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            getch();
        }
    } while (pilih != 0);

    return 0;
}

// Fungsi untuk menambahkan mahasiswa ke dalam lingkaran
void tambahMahasiswa(struct node **head) {
    char nama[100];
    char jenis_kelamin;
    struct node *pNew = (struct node *)malloc(sizeof(struct node));

    system("cls");
    printf("Masukkan nama mahasiswa/i: ");
    scanf("%s", nama);
    printf("Jenis kelamin L/P: ");
    scanf(" %c", &jenis_kelamin);

    // Cek jika jumlah peserta melebihi 20
    struct node *pCur = *head;
    int count = 0;
    if (pCur != NULL) {
        do {
            count++;
            pCur = pCur->next;
        } while (pCur != *head);
    }

    if (count >= 20) {
        printf("Tidak dapat menambahkan mahasiswa. Lingkaran sudah penuh.\n");
        getch();
        return;
    }

    // Cek jika mahasiswa yang ditambahkan adalah Cindy
    if (strcmp(nama, "Cindy") == 0) {
        int jumlahMahasiswi = 0;
        struct node *temp = *head;

        if (temp != NULL) {
            do {
                if (temp->jenis_kelamin == 'P') {
                    jumlahMahasiswi++;
                }
                temp = temp->next;
            } while (temp != *head);
        }

        if (jumlahMahasiswi < 2) {
            printf("Cindy tidak dapat bergabung karena tidak ada cukup mahasiswi lainnya dalam lingkaran.\n");
            getch();
            return;
        }
    }

    // Cek jika mahasiswa yang ditambahkan adalah Arsyad
    if (strcmp(nama, "Arsyad") == 0) {
        struct node *pNewIrysad = (struct node *)malloc(sizeof(struct node));
        strcpy(pNew->nama, "Arsyad");
        pNew->jenis_kelamin = 'L';
        strcpy(pNewIrysad->nama, "Irysad");
        pNewIrysad->jenis_kelamin = 'L';

        // Menambahkan Arsyad dan Irysad ke dalam lingkaran
        if (*head == NULL) {
            pNew->next = pNewIrysad;
            pNewIrysad->next = pNew;
            *head = pNew;
        } else {
            struct node *pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->next = pNewIrysad;
            pNewIrysad->next = *head;
        }
        printf("Arsyad dan Irysad berhasil ditambahkan ke dalam lingkaran.\n");
        getch();
        return;
    }

    // Cek jika mahasiswa yang ditambahkan adalah Irsyad
    if (strcmp(nama, "Irsyad") == 0) {
        struct node *pNewArysad = (struct node *)malloc(sizeof(struct node));
        strcpy(pNew->nama, "Irsyad");
        pNew->jenis_kelamin = 'L';
        strcpy(pNewArysad->nama, "Arysad");
        pNewArysad->jenis_kelamin = 'L';

        // Menambahkan Irsyad dan Arysad ke dalam lingkaran
        if (*head == NULL) {
            pNew->next = pNewArysad;
            pNewArysad->next = pNew;
            *head = pNew;
        } else {
            struct node *pLast = *head;
            while (pLast->next != *head) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
            pNew->next = pNewArysad;
            pNewArysad->next = *head;
        }
        printf("Irsyad dan Arysad berhasil ditambahkan ke dalam lingkaran.\n");
        getch();
        return;
    }

    // Menambahkan mahasiswa baru
    if (pNew != NULL) {
        strcpy(pNew->nama, nama);
        pNew->jenis_kelamin = jenis_kelamin;

        if (*head == NULL) {
            pNew->next = pNew; // Menjadikan circular
            *head = pNew;
        } else {
            struct node *pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head;
        }

        printf("Mahasiswa bernama %s dengan jenis kelamin %c berhasil ditambahkan.\n", pNew->nama, pNew->jenis_kelamin);
        getch();
    } else {
        printf("Alokasi memori gagal.\n");
        getch();
    }
}

void keluarLingkaran(struct node **head) {
    char nama[100];
    struct node *pCur, *pPrev;
    int found = 0;

    system("cls");
    printf("Masukkan nama mahasiswa/i yang ingin keluar dari lingkaran: ");
    scanf("%s", nama);

    if (*head == NULL) {
        printf("List kosong, tidak ada mahasiswa.\n");
        getch();
        return;
    }

    pCur = *head;
    pPrev = NULL;

    // Mencari mahasiswa yang ingin keluar
    do {
        if (strcmp(pCur->nama, nama) == 0) {
            found = 1;
            break;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
        getch();
        return;
    }

    // Menghapus mahasiswa yang ditemukan
    if (pCur == *head) {
        if (pCur->next == *head) {
            free(pCur);
            *head = NULL;
        } else {
            struct node *temp = *head;
            while (temp->next != *head) {
                temp = temp->next;
            }
            *head = (*head)->next;
            temp->next = *head;
            free(pCur);
        }
    } else {
        pPrev->next = pCur->next;
        free(pCur);
    }

    printf("%s berhasil keluar dari lingkaran.\n", nama);
    getch();
}

void pisahkanLingkaran(struct node *head) {
    if (head == NULL) {
        printf("List kosong, tidak ada mahasiswa.\n");
        getch();
        return;
    }

    struct node *pCur = head;
    struct node *pCurPria = NULL;
    struct node *pCurWanita = NULL;
    struct node *headPriaTemp = NULL;
    struct node *headWanitaTemp = NULL;

    do {
        struct node *pNew = (struct node *)malloc(sizeof(struct node));
        strcpy(pNew->nama, pCur->nama);
        pNew->jenis_kelamin = pCur->jenis_kelamin;

        // Pisahkan berdasarkan jenis kelamin
        if (pCur->jenis_kelamin == 'L') {
            if (headPriaTemp == NULL) {
                headPriaTemp = pNew;
                pCurPria = pNew;
            } else {
                pCurPria->next = pNew;
                pCurPria = pCurPria->next;
            }
            pCurPria->next = headPriaTemp; // Lingkaran pria
        } else {
            if (headWanitaTemp == NULL) {
                headWanitaTemp = pNew;
                pCurWanita = pNew;
            } else {
                pCurWanita->next = pNew;
                pCurWanita = pCurWanita->next;
            }
            pCurWanita->next = headWanitaTemp; // Lingkaran wanita
        }
        pCur = pCur->next;
    } while (pCur != head);

    // Menyimpan hasil
    headPria = headPriaTemp;
    headWanita = headWanitaTemp;

    // Tampilkan hasil
    printf("Lingkaran berhasil dipisahkan menjadi dua:\n");

    // Tampilkan mahasiswa pria
    printf("Mahasiswa Pria:\n");
    if (headPria == NULL) {
        printf("List kosong.\n");
    } else {
        struct node *pCur = headPria;
        do {
            printf("%s -> ", pCur->nama);
            pCur = pCur->next;
        } while (pCur != headPria);
        printf("%s (kembali ke awal)\n", headPria->nama); // Kembali ke nama kepala
    }

    // Tampilkan mahasiswa wanita
    printf("Mahasiswa Wanita:\n");
    if (headWanita == NULL) {
        printf("List kosong.\n");
    } else {
        struct node *pCur = headWanita;
        do {
            printf("%s -> ", pCur->nama);
            pCur = pCur->next;
        } while (pCur != headWanita);
        printf("%s (kembali ke awal)\n", headWanita->nama); // Kembali ke nama kepala
    }

    getch();
}

void cetakIsiList(struct node *head) {
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    struct node *pCur = head;
    printf("Status Mahasiswa:\n");
    do {
        printf("%s -> ", pCur->nama);
        pCur = pCur->next;
    } while (pCur != head);
    printf("%s (kembali ke awal)\n", head->nama); // Kembali ke nama kepala
}

