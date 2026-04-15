#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
    string pemilik;
    string keluhan;
    Hewan* next;
};

struct Queue {
    Hewan* front;
    Hewan* rear;
    
    Queue() : front(nullptr), rear(nullptr) {}
};

struct Stack {
    Hewan* top;
    
    Stack() : top(nullptr) {}
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string inputTidakKosong(string pesan) {
    string input;
    bool hanyaSpasi;

    do {
        cout << pesan;
        getline(cin, input);

        hanyaSpasi = true;
        for (char c : input) {
            if (!isspace(c)) {
                hanyaSpasi = false;
                break;
            }
        }

        if (input.empty() || hanyaSpasi) {
            cout << "Input tidak boleh kosong!" << endl;
        }

    } while (input.empty() || hanyaSpasi);

    return input;
}

void swapHewan(Hewan* a, Hewan* b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

Hewan* createNode(int id, string nama, string jenis, string pemilik, string keluhan, double harga) {
    Hewan* newNode = new Hewan;
    newNode -> id = id;
    newNode -> nama = nama;
    newNode -> jenis = jenis;
    newNode -> pemilik = pemilik;
    newNode -> keluhan = keluhan;
    newNode -> harga = harga;
    newNode -> next = nullptr;
    return newNode;
}

void deleteNode(Hewan* node) {
    delete node;
}

void tampilkanHeaderTabel() {
    cout << "\n" << setfill('=') << setw(91) << "" << endl;
    cout << setfill(' ');
    cout << "| " << setw(5) << "ID" << " | " 
         << setw(15) << "Nama Hewan" << " | " 
         << setw(15) << "Jenis" << " | " 
         << setw(10) << "Pemilik" << " | "
         << setw(15) << "Keluhan" << " | "
         << setw(12) << "Harga (Rp)" << " |" << endl;
    cout << setfill('=') << setw(91) << "" << endl;
    cout << setfill(' ');
}

void tampilkanFooterTabel() {
    cout << setfill('-') << setw(91) << "" << endl;
    cout << setfill(' ');
}

void tampilkanData(Hewan* head, int n) {
    if (n == 0 || head == nullptr) {
        cout << "Data masih kosong!" << endl;
        return;
    }

    tampilkanHeaderTabel();
    Hewan* current = head;
    while (current != nullptr) {
        cout << "| " << setw(5) << current -> id << " | " 
             << setw(15) << current -> nama << " | " 
             << setw(15) << current -> jenis << " | "
             << setw(10) << current -> pemilik << " | "
             << setw(15) << current -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << current -> harga << " |" << endl;
        current = current -> next;
    }
    tampilkanFooterTabel();
}

void initQueue(Queue* q) {
    q -> front = nullptr;
    q -> rear = nullptr;
}

bool isQueueEmpty(Queue* q) {
    return (q -> front == nullptr);
}

bool isHewanInQueue(Queue* q, int idHewan) {
    if (isQueueEmpty(q)) {
        return false;
    }
    
    Hewan* current = q -> front;
    while (current != nullptr) {
        if (current -> id == idHewan) {
            return true;
        }
        current = current -> next;
    }
    return false;
}

void enqueue(Queue* q, Hewan hewan) {
    Hewan* newNode = createNode(hewan.id, hewan.nama, hewan.jenis, 
                                 hewan.pemilik, hewan.keluhan, hewan.harga);
    
    if (newNode == nullptr) {
        cout << "Gagal mengalokasikan memori!" << endl;
        return;
    }
    
    if (isHewanInQueue(q, hewan.id)) {
        cout << "Hewan dengan ID " << hewan.id 
             << " (" << hewan.nama << ") sudah ada dalam antrian!" << endl;
        cout << "Tidak dapat menambahkan hewan yang sama ke antrian dua kali." << endl;
        deleteNode(newNode);
        return;
    }
    
    if (isQueueEmpty(q)) {
        q -> front = newNode;
        q -> rear = newNode;
    } else {
        q -> rear -> next = newNode;
        q -> rear = newNode;
    }
    
    cout << hewan.nama << " (ID: " << hewan.id << ") telah ditambahkan ke antrian." << endl;
}

Hewan dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Queue underflow! Antrian kosong." << endl;
        Hewan kosong;
        kosong.id = -1;
        kosong.next = nullptr;
        return kosong;
    }
    
    Hewan* temp = q -> front;
    Hewan hewanDipanggil = *temp;
    
    q -> front = q -> front -> next;
    
    if (q -> front == nullptr) {
        q -> rear = nullptr;
    }
    
    deleteNode(temp);
    return hewanDipanggil;
}

void tampilkanAntrian(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Antrian kosong." << endl;
        return;
    }
    
    tampilkanHeaderTabel();
    
    Hewan* current = q -> front;
    int count = 0;
    while (current != nullptr) {
        cout << "| " << setw(5) << current -> id << " | " 
             << setw(15) << current -> nama << " | " 
             << setw(15) << current -> jenis << " | "
             << setw(10) << current -> pemilik << " | "
             << setw(15) << current -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << current -> harga << " |" << endl;
        current = current -> next;
        count++;
    }
    tampilkanFooterTabel();
    cout << "Total antrian: " << count << " pasien" << endl;
}

void peekAntrian(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Antrian kosong." << endl;
        return;
    }
    
    Hewan* depan = q -> front;
    cout << "\n=== PASIEN TERDEPAN ===" << endl;
    cout << "ID      : " << depan -> id << endl;
    cout << "Nama    : " << depan -> nama << endl;
    cout << "Jenis   : " << depan -> jenis << endl;
    cout << "Pemilik : " << depan -> pemilik << endl;
    cout << "Keluhan : " << depan -> keluhan << endl;
    cout << "Harga   : Rp " << fixed << setprecision(0) << depan -> harga << endl;
}

void initStack(Stack* s) {
    s -> top = nullptr;
}

bool isStackEmpty(Stack* s) {
    return (s -> top == nullptr);
}

void push(Stack* s, Hewan hewan) {
    Hewan* newNode = createNode(hewan.id, hewan.nama, hewan.jenis, hewan.pemilik, hewan.keluhan, hewan.harga);
    
    if (newNode == nullptr) {
        cout << "Gagal mengalokasikan memori!" << endl;
        return;
    }
    
    newNode -> next = s -> top;
    s -> top = newNode;
    
    cout << "Tindakan untuk " << hewan.nama << " (ID: " << hewan.id << ") telah dicatat ke riwayat." << endl;
}

Hewan pop(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Stack underflow! Riwayat kosong." << endl;
        Hewan kosong;
        kosong.id = -1;
        kosong.next = nullptr;
        return kosong;
    }
    
    Hewan* temp = s -> top;
    Hewan hewanDihapus = *temp;
    
    s -> top = s -> top -> next;
    deleteNode(temp);
    
    return hewanDihapus;
}

void tampilkanRiwayat(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Riwayat tindakan kosong." << endl;
        return;
    }
    
    cout << "\n========== RIWAYAT TINDAKAN MEDIS ==========" << endl;
    tampilkanHeaderTabel();
    
    const int MAX_TEMP = 1000;
    Hewan* tempArray[MAX_TEMP];
    int count = 0;
    
    Hewan* current = s -> top;
    while (current != nullptr && count < MAX_TEMP) {
        tempArray[count++] = current;
        current = current -> next;
    }
    
    for (int i = count - 1; i >= 0; i--) {
        cout << "| " << setw(5) << tempArray[i] -> id << " | " 
             << setw(15) << tempArray[i] -> nama << " | " 
             << setw(15) << tempArray[i] -> jenis << " | "
             << setw(10) << tempArray[i] -> pemilik << " | "
             << setw(15) << tempArray[i] -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << tempArray[i] -> harga << " |" << endl;
    }
    tampilkanFooterTabel();
    cout << "Total tindakan: " << count << endl;
}

void peekRiwayat(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Riwayat kosong." << endl;
        return;
    }
    
    Hewan* terakhir = s -> top;
    cout << "\n=== TINDAKAN TERAKHIR ===" << endl;
    cout << "ID      : " << terakhir -> id << endl;
    cout << "Nama    : " << terakhir -> nama << endl;
    cout << "Jenis   : " << terakhir -> jenis << endl;
    cout << "Pemilik : " << terakhir -> pemilik << endl;
    cout << "Keluhan : " << terakhir -> keluhan << endl;
    cout << "Harga   : Rp " << fixed << setprecision(0) << terakhir -> harga << endl;
}

void tambahHewan(Hewan** head, int* n) {
    cout << "========= TAMBAH HEWAN =========\n";

    int inputID;
    bool duplikat;

    do {
        cout << "Masukkan ID Hewan   : ";
        while (!(cin >> inputID)) {
            cout << "Input ID harus angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        duplikat = false;
        Hewan* current = *head;
        while (current != nullptr) {
            if (current -> id == inputID) {
                duplikat = true;
                break;
            }
            current = current -> next;
        }

        if (duplikat) {
            cout << "ID sudah digunakan! Masukkan ID lain.\n";
        }

    } while (duplikat);

    cin.ignore();

    string nama = inputTidakKosong("Masukkan Nama Hewan : ");
    string jenis = inputTidakKosong("Masukkan Jenis      : ");
    string pemilik = inputTidakKosong("Masukkan Nama Pemilik: ");
    string keluhan = inputTidakKosong("Masukkan Keluhan    : ");

    double harga;
    cout << "Masukkan Biaya      : ";
    while (!(cin >> harga) || harga < 0) {
        cout << "Biaya harus angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Hewan* newNode = createNode(inputID, nama, jenis, pemilik, keluhan, harga);
    newNode -> next = *head;
    *head = newNode;
    (*n)++;

    cout << "\nData berhasil ditambahkan!" << endl;
}

int getListLength(Hewan* head) {
    int count = 0;
    Hewan* current = head;
    while (current != nullptr) {
        count++;
        current = current -> next;
    }
    return count;
}

Hewan* linkedListToArray(Hewan* head, int n) {
    Hewan* arr = new Hewan[n];
    Hewan* current = head;
    for (int i = 0; i < n && current != nullptr; i++) {
        arr[i] = *current;
        current = current -> next;
    }
    return arr;
}

Hewan* arrayToLinkedList(Hewan* arr, int n) {
    if (n == 0) return nullptr;
    
    Hewan* head = createNode(arr[0].id, arr[0].nama, arr[0].jenis, 
                              arr[0].pemilik, arr[0].keluhan, arr[0].harga);
    Hewan* current = head;
    
    for (int i = 1; i < n; i++) {
        current -> next = createNode(arr[i].id, arr[i].nama, arr[i].jenis,
                                    arr[i].pemilik, arr[i].keluhan, arr[i].harga);
        current = current -> next;
    }
    
    return head;
}

void bubbleSortNama(Hewan** head) {
    cout << "========= SORT NAMA (A-Z) =========\n";
    
    int n = getListLength(*head);
    if (n <= 1) {
        cout << "Data sudah terurut atau kosong!\n";
        return;
    }
    
    Hewan* arr = linkedListToArray(*head, n);
    
    for (int i = 0; i < n - 1; i++) {
        bool adaSwap = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) {
                swapHewan(&arr[j], &arr[j + 1]);
                adaSwap = true;
            }
        }
        
        if (!adaSwap) break;
    }
    
    Hewan* current = *head;
    while (current != nullptr) {
        Hewan* temp = current;
        current = current -> next;
        deleteNode(temp);
    }
    
    *head = arrayToLinkedList(arr, n);
    delete[] arr;
    
    cout << "Sorting berhasil!\n";
}

void selectionSortHarga(Hewan** head) {
    cout << "========= SORT BIAYA TERMURAH =========\n";
    
    int n = getListLength(*head);
    if (n <= 1) {
        cout << "Data sudah terurut atau kosong!\n";
        return;
    }
    
    Hewan* arr = linkedListToArray(*head, n);
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[minIdx].harga) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            swapHewan(&arr[minIdx], &arr[i]);
        }
    }
    
    Hewan* current = *head;
    while (current != nullptr) {
        Hewan* temp = current;
        current = current -> next;
        deleteNode(temp);
    }
    
    *head = arrayToLinkedList(arr, n);
    delete[] arr;
    
    cout << "Sorting berhasil!\n";
}

void sortByID(Hewan** head) {
    int n = getListLength(*head);
    if (n <= 1) return;
    
    Hewan* arr = linkedListToArray(*head, n);
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].id < arr[minIdx].id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapHewan(&arr[minIdx], &arr[i]);
        }
    }
    
    Hewan* current = *head;
    while (current != nullptr) {
        Hewan* temp = current;
        current = current -> next;
        deleteNode(temp);
    }
    
    *head = arrayToLinkedList(arr, n);
    delete[] arr;
}

void linearSearchNama(Hewan* head, string target) {
    cout << "\n========= LINEAR SEARCH =========\n";
    cout << "Mencari hewan dengan nama: " << target << endl;

    bool found = false;
    int count = 0;
    
    const int MAX_FOUND = 100;
    Hewan* foundNodes[MAX_FOUND];
    
    Hewan* current = head;
    while (current != nullptr && count < MAX_FOUND) {
        if (current -> nama == target) {
            foundNodes[count++] = current;
            found = true;
        }
        current = current -> next;
    }

    if (found) {
        cout << "\nDitemukan " << count << " data:\n";
        tampilkanHeaderTabel();
        for (int i = 0; i < count; i++) {
            cout << "| " << setw(5) << foundNodes[i] -> id << " | " 
                 << setw(15) << foundNodes[i] -> nama << " | " 
                 << setw(15) << foundNodes[i] -> jenis << " | "
                 << setw(10) << foundNodes[i] -> pemilik << " | "
                 << setw(15) << foundNodes[i] -> keluhan << " | "
                 << setw(12) << foundNodes[i] -> harga << " |" << endl;
        }
        tampilkanFooterTabel();
    } else {
        cout << "\nData dengan nama '" << target << "' tidak ditemukan.\n";
    }
}

int minVal(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearchID(Hewan** head, int x) {
    cout << "\n========= FIBONACCI SEARCH =========\n";
    cout << "Mencari hewan dengan ID: " << x << endl;

    sortByID(head);
    
    int n = getListLength(*head);
    Hewan* arr = linkedListToArray(*head, n);
    
    int fibM2 = 0;
    int fibM1 = 1;
    int fibM = fibM2 + fibM1;

    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    int offset = -1;
    bool found = false;
    int foundIndex = -1;

    while (fibM > 1) {
        int i = minVal(offset + fibM2, n - 1);

        if (arr[i].id < x) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if (arr[i].id > x) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else {
            found = true;
            foundIndex = i;
            break;
        }
    }

    if (!found && fibM1 && (offset + 1 < n) && arr[offset + 1].id == x) {
        found = true;
        foundIndex = offset + 1;
    }

    if (found) {
        if (foundIndex != 0) {
            swapHewan(&arr[foundIndex], &arr[0]);
        }
        
        tampilkanHeaderTabel();
        cout << "| " << setw(5) << arr[0].id << " | "
             << setw(15) << arr[0].nama << " | "
             << setw(15) << arr[0].jenis << " | "
             << setw(10) << arr[0].pemilik << " | "
             << setw(15) << arr[0].keluhan << " | "
             << setw(12) << arr[0].harga << " |" << endl;
        tampilkanFooterTabel();
        
        Hewan* current = *head;
        while (current != nullptr) {
            Hewan* temp = current;
            current = current -> next;
            deleteNode(temp);
        }
        *head = arrayToLinkedList(arr, n);
    } else {
        cout << "\nData dengan ID " << x << " tidak ditemukan.\n";
    }
    
    delete[] arr;
}

Hewan* cariHewanByID(Hewan* head, int id) {
    Hewan* current = head;
    while (current != nullptr) {
        if (current -> id == id) {
            return current;
        }
        current = current -> next;
    }
    return nullptr;
}

void deleteAllNodes(Hewan* head) {
    while (head != nullptr) {
        Hewan* temp = head;
        head = head -> next;
        deleteNode(temp);
    }
}

int main() {
    Hewan* daftarHewan = createNode(105, "Francis", "Kucing", "Budi", "Demam", 1500000);
    daftarHewan -> next = createNode(102, "Golden", "Anjing", "Siti", "Muntah", 4500000);
    daftarHewan -> next -> next = createNode(108, "Winter", "Hamster", "Rina", "Luka", 50000);
    daftarHewan -> next -> next -> next = createNode(101, "Guana", "Reptil", "Andi", "Nafsu makan", 750000);
    daftarHewan -> next -> next -> next -> next = createNode(104, "Noctua", "Burung", "Dewi", "Bulu rontok", 2500000);
    daftarHewan -> next -> next -> next -> next -> next = createNode(103, "Milo", "Kucing", "Joko", "Batuk", 2000000);
    daftarHewan -> next -> next -> next -> next -> next -> next = createNode(107, "Bobby", "Anjing", "Lisa", "Diare", 3500000);
    daftarHewan -> next -> next -> next -> next -> next -> next -> next = createNode(106, "Kiki", "Burung", "Maya", "Mata berair", 500000);

    int jumlahHewan = 8;
    int pilihan;
    
    Queue antrian;
    Stack riwayat;
    
    initQueue(&antrian);
    initStack(&riwayat);

    do {
        system("cls||clear");

        cout << "======= PAWCARE PETSHOP & DOKTER HEWAN =======\n\n";
        cout << "============= MANAJEMEN DATA HEWAN ============" << endl;
        cout << "1. Tambahkan Hewan" << endl;
        cout << "2. Tampilkan Semua Hewan" << endl;
        cout << "3. Cari Berdasarkan Nama" << endl;
        cout << "4. Cari Berdasarkan ID" << endl;
        cout << "5. Urutkan Berdasarkan Nama" << endl;
        cout << "6. Urutkan Berdasarkan Harga" << endl;
        cout << "\n============= MANAJEMEN ANTRIAN ============" << endl;
        cout << "7. Tambah Pasien ke Antrian" << endl;
        cout << "8. Panggil Pasien & Catat Riwayat" << endl;
        cout << "9. Tampilkan Semua Antrian" << endl;
        cout << "10. Lihat Pasien Terdepan" << endl;
        cout << "\n============= MANAJEMEN RIWAYAT ============" << endl;
        cout << "11. Tampilkan Riwayat Tindakan" << endl;
        cout << "12. Batalkan Tindakan Terakhir" << endl;
        cout << "13. Lihat Tindakan Terakhir" << endl;
        cout << "\n14. Keluar" << endl;

        cout << "\nPilih Menu: ";
        while (!(cin >> pilihan)) {
            cout << "Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        system("cls||clear");

        switch (pilihan) {
            case 1: {
                tambahHewan(&daftarHewan, &jumlahHewan);
                break;
            }

            case 2:
                cout << "========= DATA HEWAN PAWCARE =========\n";
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 3: {
                cout << "========= CARI NAMA =========\n";
                cin.ignore();
                string nama = inputTidakKosong("Masukkan Nama Hewan: ");
                linearSearchNama(daftarHewan, nama);
                break;
            }

            case 4: {
                cout << "========= CARI ID =========\n";
                int id;
                cout << "Masukkan ID Hewan: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                fibonacciSearchID(&daftarHewan, id);
                break;
            }

            case 5:
                bubbleSortNama(&daftarHewan);
                cout << "\nData setelah diurutkan berdasarkan Nama (A-Z):\n";
                tampilkanData(daftarHewan, getListLength(daftarHewan));
                break;

            case 6:
                selectionSortHarga(&daftarHewan);
                cout << "\nData setelah diurutkan berdasarkan Biaya (Termurah):\n";
                tampilkanData(daftarHewan, getListLength(daftarHewan));
                break;
                
            case 7: {
                cout << "========= TAMBAH PASIEN =========\n";
                int idHewan;
                cout << "Masukkan ID Hewan yang akan diantrikan: ";
                while (!(cin >> idHewan)) {
                    cout << "Input ID harus angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                Hewan* hewanDitemukan = cariHewanByID(daftarHewan, idHewan);
                if (hewanDitemukan != nullptr) {
                    enqueue(&antrian, *hewanDitemukan);
                } else {
                    cout << "Hewan dengan ID " << idHewan << " tidak ditemukan!" << endl;
                }
                break;
            }
            
            case 8: {
                cout << "========= PANGGIL PASIEN =========\n";
                Hewan pasien = dequeue(&antrian);
                if (pasien.id != -1) {
                    cout << "\nMEMANGGIL PASIEN:" << endl;
                    cout << "Nama : " << pasien.nama << endl;
                    cout << "ID   : " << pasien.id << endl;
                    cout << "Pemilik : " << pasien.pemilik << endl;
                    cout << "Keluhan : " << pasien.keluhan << endl;
                    
                    push(&riwayat, pasien);
                    cout << "\nPasien telah selesai diperiksa dan dicatat ke riwayat." << endl;
                }
                break;
            }
            
            case 9:
                cout << "========= TAMPILKAN ANTRIAN =========\n";
                tampilkanAntrian(&antrian);
                break;
                
            case 10:
                cout << "========= PEEK ANTRIAN =========\n";
                peekAntrian(&antrian);
                break;
                
            case 11:
                tampilkanRiwayat(&riwayat);
                break;
                
            case 12: {
                cout << "========= POP RIWAYAT =========\n";
                Hewan dibatalkan = pop(&riwayat);
                if (dibatalkan.id != -1) {
                    cout << "Tindakan untuk " << dibatalkan.nama 
                         << " (ID: " << dibatalkan.id << ") telah dibatalkan/dihapus dari riwayat." << endl;
                }
                break;
            }
                
            case 13:
                cout << "========= PEEK RIWAYAT =========\n";
                peekRiwayat(&riwayat);
                break;

            case 14:
                cout << "Terima kasih telah menggunakan Pawcare Petshop!" << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }

        if (pilihan != 14) {
            cout << "\n";
            system("pause");
        }

    } while (pilihan != 14);

    deleteAllNodes(daftarHewan);

    while (!isQueueEmpty(&antrian)) {
        dequeue(&antrian);
    }
    
    while (!isStackEmpty(&riwayat)) {
        pop(&riwayat);
    }

    return 0;
}