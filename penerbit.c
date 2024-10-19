#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PUBLISHERS 50
#define MAX_NAME 100
#define MAX_ADDRESS 200
#define MAX_PHONE 15
#define MAX_EMAIL 50

// Struktur data untuk penerbit
struct Publisher {
    int id;
    char name[MAX_NAME];
    char address[MAX_ADDRESS];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    int isActive; // 1 = active, 0 = deleted
};

// Array untuk menyimpan penerbit
struct Publisher publishers[MAX_PUBLISHERS];
int publisherCount = 0;

// Function prototypes
void addPublisher();
void editPublisher();
void deletePublisher();
void searchPublisher();
void displayPublisher(struct Publisher pub);
void displayAllPublishers();
int findPublisherById(int id);
void clearScreen();

int main() {
    int choice;
    
    do {
        printf("\n=== Penerbit ===\n");
        printf("1. Tambah Penerbit\n");
        printf("2. Edit Penerbit\n");
        printf("3. Hapus Penerbit\n");
        printf("4. Cari Penerbit\n");
        printf("5. Tampilkan Semua Penerbit\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clearScreen();
        
        switch(choice) {
            case 1:
                addPublisher();
                break;
            case 2:
                editPublisher();
                break;
            case 3:
                deletePublisher();
                break;
            case 4:
                searchPublisher();
                break;
            case 5:
                displayAllPublishers();
                break;
        }
    } while(choice != 0);
    
    return 0;
}

void addPublisher() {
    if(publisherCount >= MAX_PUBLISHERS) {
        printf("Database penuh!\n");
        return;
    }
    
    struct Publisher newPub;
    newPub.id = publisherCount + 1;
    newPub.isActive = 1;
    
    printf("=== Tambah Penerbit Baru ===\n");
    printf("Nama Penerbit: ");
    getchar();
    fgets(newPub.name, MAX_NAME, stdin);
    newPub.name[strcspn(newPub.name, "\n")] = 0;
    
    printf("Alamat: ");
    fgets(newPub.address, MAX_ADDRESS, stdin);
    newPub.address[strcspn(newPub.address, "\n")] = 0;
    
    printf("Nomor Telepon: ");
    fgets(newPub.phone, MAX_PHONE, stdin);
    newPub.phone[strcspn(newPub.phone, "\n")] = 0;
    
    printf("Email: ");
    fgets(newPub.email, MAX_EMAIL, stdin);
    newPub.email[strcspn(newPub.email, "\n")] = 0;
    
    publishers[publisherCount] = newPub;
    publisherCount++;
    
    printf("\nPenerbit berhasil ditambahkan!\n");
}

void editPublisher() {
    int id;
    printf("Masukkan ID penerbit yang akan diedit: ");
    scanf("%d", &id);
    
    int index = findPublisherById(id);
    if(index == -1) {
        printf("Penerbit tidak ditemukan!\n");
        return;
    }
    
    printf("=== Edit Penerbit ===\n");
    printf("Nama Penerbit [%s]: ", publishers[index].name);
    getchar();
    fgets(publishers[index].name, MAX_NAME, stdin);
    publishers[index].name[strcspn(publishers[index].name, "\n")] = 0;
    
    printf("Alamat [%s]: ", publishers[index].address);
    fgets(publishers[index].address, MAX_ADDRESS, stdin);
    publishers[index].address[strcspn(publishers[index].address, "\n")] = 0;
    
    printf("Nomor Telepon [%s]: ", publishers[index].phone);
    fgets(publishers[index].phone, MAX_PHONE, stdin);
    publishers[index].phone[strcspn(publishers[index].phone, "\n")] = 0;
    
    printf("Email [%s]: ", publishers[index].email);
    fgets(publishers[index].email, MAX_EMAIL, stdin);
    publishers[index].email[strcspn(publishers[index].email, "\n")] = 0;
    
    printf("\nData penerbit berhasil diupdate!\n");
}

void deletePublisher() {
    int id;
    printf("Masukkan ID penerbit yang akan dihapus: ");
    scanf("%d", &id);
    
    int index = findPublisherById(id);
    if(index == -1) {
        printf("Penerbit tidak ditemukan!\n");
        return;
    }
    
    char confirm;
    printf("Yakin ingin menghapus penerbit '%s'? (y/n): ", publishers[index].name);
    getchar();
    scanf("%c", &confirm);
    
    if(confirm == 'y' || confirm == 'Y') {
        publishers[index].isActive = 0;
        printf("\nPenerbit berhasil dihapus!\n");
    } else {
        printf("\nPenghapusan dibatalkan!\n");
    }
}

void searchPublisher() {
    char keyword[MAX_NAME];
    int found = 0;
    
    printf("Masukkan kata kunci pencarian: ");
    getchar();
    fgets(keyword, MAX_NAME, stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    
    printf("\n=== Hasil Pencarian ===\n");
    for(int i = 0; i < publisherCount; i++) {
        if(publishers[i].isActive && 
           (strstr(publishers[i].name, keyword) || 
            strstr(publishers[i].address, keyword) || 
            strstr(publishers[i].email, keyword))) {
            displayPublisher(publishers[i]);
            found = 1;
        }
    }
    
    if(!found) {
        printf("Tidak ada penerbit yang ditemukan!\n");
    }
}

void displayPublisher(struct Publisher pub) {
    if(pub.isActive) {
        printf("\nID: %d\n", pub.id);
        printf("Nama: %s\n", pub.name);
        printf("Alamat: %s\n", pub.address);
        printf("Telepon: %s\n", pub.phone);
        printf("Email: %s\n", pub.email);
        printf("------------------------\n");
    }
}

void displayAllPublishers() {
    printf("\n=== Daftar Semua Penerbit ===\n");
    int found = 0;
    
    for(int i = 0; i < publisherCount; i++) {
        if(publishers[i].isActive) {
            displayPublisher(publishers[i]);
            found = 1;
        }
    }
    
    if(!found) {
        printf("Tidak ada penerbit dalam database!\n");
    }
}

int findPublisherById(int id) {
    for(int i = 0; i < publisherCount; i++) {
        if(publishers[i].id == id && publishers[i].isActive) {
            return i;
        }
    }
    return -1;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}