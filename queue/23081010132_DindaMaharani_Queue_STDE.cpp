#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//========================================================
struct node {
    int data;
    struct node *next;
};
typedef struct node node;

struct queue {
    int count;
    int maxSize;  // Menyimpan ukuran maksimal dari queue
    node *front;
    node *rear;
};
typedef struct queue queue;

queue myQueue;

queue createQueue(int maxSize) {
    myQueue.count = 0;
    myQueue.maxSize = maxSize;  // Atur ukuran maksimal queue
    myQueue.front = NULL;
    myQueue.rear = NULL;
    return myQueue;
}

void enqueue();
void dequeue();
void queuefront();
void queuerear();
bool emptyqueue();
bool fullqueue();
void queueCount();
void destroyqueue();
void displayqueue();

int main() {
    int pilih, maxQueueSize;
    
    // Minta user untuk memasukkan ukuran maksimal queue
    printf("Masukkan ukuran maksimal queue: ");
    scanf("%d", &maxQueueSize);
    getchar();  // Mengatasi enter setelah input angka

    // Buat queue dengan ukuran maksimal yang diinput user
    createQueue(maxQueueSize);

    do {
        system("cls");
        printf("Menu pilihan\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Queue Front\n");
        printf("4. Queue Rear\n");
        printf("5. Destroy Queue\n");
        printf("6. Full Queue\n");
        printf("7. Empty Queue\n");
        printf("8. Queue Count\n");
        printf("9. Display Queue\n");
        printf("Masukkan angka sesuai pilihan! (masukkan 0 untuk keluar) : ");
        scanf("%d", &pilih);
        getchar(); // Untuk menangani enter setelah input

        if (pilih == 1)
            enqueue();
        else if (pilih == 2)
            dequeue();
        else if (pilih == 3)
            queuefront();
        else if (pilih == 4)
            queuerear();
        else if (pilih == 5)
            destroyqueue();
        else if (pilih == 6) {
            printf("%s\n", fullqueue() ? "Queue penuh!" : "Queue tidak penuh.");
            getchar();
        }
        else if (pilih == 7) {
            printf("%s\n", emptyqueue() ? "Queue kosong!" : "Queue tidak kosong.");
            getchar();
        }
        else if (pilih == 8)
            queueCount();
        else if (pilih == 9)
            displayqueue();
        
    } while (pilih != 0);
    
    return 0;
}

void enqueue() {
    if (fullqueue()) {
        printf("Queue penuh!\n");
        getchar();
        return;
    }
    
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    printf("Masukkan bilangan : ");
    scanf("%d", &bil);
    getchar();

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (myQueue.front == NULL) {
            myQueue.front = pNew;
        } else {
            myQueue.rear->next = pNew;
        }
        myQueue.rear = pNew;
        myQueue.count++;
        printf("Data %d berhasil ditambahkan ke dalam Queue\n", bil);
        getchar();
    } else {
        printf("Alokasi memori gagal\n");
        getchar();
    }
}

void dequeue() {
    if (emptyqueue()) {
        printf("queue kosong!\n");
        getchar();
        return;
    }
    
    node *dltPtr = myQueue.front;
    myQueue.front = myQueue.front->next;

    if (myQueue.front == NULL) {
        myQueue.rear = NULL;
    }

    printf("Data %d berhasil dihapus.\n", dltPtr->data);
    free(dltPtr);
    myQueue.count--;
    getchar();
}

void queuefront() {
    if (emptyqueue()) {
        printf("queue kosong tidak ditemukan front di dalamnya!\n");
        getchar();
    } else {
        printf("data paling depan dalam queue: %d\n", myQueue.front->data);
        getchar();
    }
}

void queuerear() {
    if (emptyqueue()) {
        printf("queue kosong tidak ditemukan rear didalamnya!\n");
        getchar();
    } else {
        printf("data paling belakang dalam queue: %d\n", myQueue.rear->data);
        getchar();
    }
}

bool emptyqueue() {
    return myQueue.count == 0;
}

bool fullqueue() {
    return myQueue.count >= myQueue.maxSize;  // Periksa apakah queue penuh berdasarkan ukuran maksimal
}

void queueCount() {
    printf("Jumlah data yang ada dalam queue: %d\n", myQueue.count);
    getchar();
}

void destroyqueue() {
    while (myQueue.front != NULL) {
        node *temp = myQueue.front;
        myQueue.front = myQueue.front->next;
        free(temp);
    }
    myQueue.rear = NULL;
    myQueue.count = 0;
    printf("queue berhasil dikosongkan\n");
    getchar();
}

void displayqueue() {
    if (emptyqueue()) {
        printf("Queue kosong, tidak ada yang bisa ditampilkan.\n");
        getchar();
    } else {
        node *temp = myQueue.front;
        printf("Isi Queue: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
        getchar();
    }
}