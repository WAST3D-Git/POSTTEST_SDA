#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

const int MAX = 100;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
    string pemilik;
    string keluhan;
};

struct Queue {
    Hewan antrian[MAX];
    int front;
    int rear;
};

struct Stack {
    Hewan riwayat[MAX];
    int top;
};

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

void tampilkanHeaderTabel() {
    cout << "\n" << setfill('=') << setw(93) << "" << endl;
    cout << setfill(' ');
    cout << "| " << setw(5) << "ID" << " | " 
         << setw(15) << "Nama Hewan" << " | " 
         << setw(15) << "Jenis" << " | " 
         << setw(10) << "Pemilik" << " | "
         << setw(15) << "Keluhan" << " | "
         << setw(12) << "Harga (Rp)" << " |" << endl;
    cout << setfill('=') << setw(93) << "" << endl;
    cout << setfill(' ');
}

void tampilkanFooterTabel() {
    cout << setfill('-') << setw(93) << "" << endl;
    cout << setfill(' ');
}

void tampilkanData(Hewan* arr, int n) {
    if (n == 0) {
        cout << "Data masih kosong!" << endl;
        return;
    }

    tampilkanHeaderTabel();
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(5) << (arr + i) -> id << " | " 
             << setw(15) << (arr + i) -> nama << " | " 
             << setw(15) << (arr + i) -> jenis << " | "
             << setw(10) << (arr + i) -> pemilik << " | "
             << setw(15) << (arr + i) -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << (arr + i) -> harga << " |" << endl;
    }
    tampilkanFooterTabel();
}

void initQueue(Queue* q) {
    q -> front = -1;
    q -> rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return (q -> front == -1);
}

bool isQueueFull(Queue* q) {
    return (q -> rear == MAX - 1);
}

bool isHewanInQueue(Queue* q, int idHewan) {
    if (isQueueEmpty(q)) {
        return false;
    }
    
    for (Hewan* ptr = q -> antrian + q -> front; ptr <= q -> antrian + q -> rear; ptr++) {
        if (ptr -> id == idHewan) {
            return true;
        }
    }
    return false;
}

void enqueue(Queue* q, Hewan hewan) {
    // Cek overflow
    if (isQueueFull(q)) {
        cout << "Queue overflow! Antrian penuh." << endl;
        return;
    }
    
    if (isHewanInQueue(q, hewan.id)) {
        cout << "Hewan dengan ID " << hewan.id 
             << " (" << hewan.nama << ") sudah ada dalam antrian!" << endl;
        cout << "Tidak dapat menambahkan hewan yang sama ke antrian dua kali." << endl;
        return;
    }
    
    if (isQueueEmpty(q)) {
        q -> front = 0;
    }
    
    q -> rear++;
    *(q -> antrian + q -> rear) = hewan;
    cout << hewan.nama << " (ID: " << hewan.id << ") telah ditambahkan ke antrian." << endl;
}

Hewan dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Queue underflow! Antrian kosong." << endl;
        Hewan kosong;
        kosong.id = -1;
        return kosong;
    }
    
    Hewan hewanDipanggil = *(q -> antrian + q -> front);
    
    q -> front++;
    if (q -> front > q -> rear) {
        q -> front = -1;
        q -> rear = -1;
    }
    
    return hewanDipanggil;
}

void tampilkanAntrian(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Antrian kosong." << endl;
        return;
    }
    
    cout << "\n========== ANTRIAN PASIEN ==========" << endl;
    tampilkanHeaderTabel();
    
    for (Hewan* ptr = q -> antrian + q -> front; ptr <= q -> antrian + q -> rear; ptr++) {
        cout << "| " << setw(5) << ptr -> id << " | " 
             << setw(15) << ptr -> nama << " | " 
             << setw(15) << ptr -> jenis << " | "
             << setw(10) << ptr -> pemilik << " | "
             << setw(15) << ptr -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << ptr -> harga << " |" << endl;
    }
    tampilkanFooterTabel();
    cout << "Total antrian: " << (q -> rear - q -> front + 1) << " pasien" << endl;
}

void peekAntrian(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Antrian kosong." << endl;
        return;
    }
    
    Hewan* depan = q -> antrian + q -> front;
    cout << "\n=== PASIEN TERDEPAN ===" << endl;
    cout << "ID      : " << depan -> id << endl;
    cout << "Nama    : " << depan -> nama << endl;
    cout << "Jenis   : " << depan -> jenis << endl;
    cout << "Pemilik : " << depan -> pemilik << endl;
    cout << "Keluhan : " << depan -> keluhan << endl;
    cout << "Harga   : Rp " << fixed << setprecision(0) << depan -> harga << endl;
}

void initStack(Stack* s) {
    s -> top = -1;
}

bool isStackEmpty(Stack* s) {
    return (s -> top == -1);
}

bool isStackFull(Stack* s) {
    return (s -> top == MAX - 1);
}

void push(Stack* s, Hewan hewan) {
    if (isStackFull(s)) {
        cout << "Stack overflow! Riwayat penuh." << endl;
        return;
    }
    
    s -> top++;
    *(s -> riwayat + s -> top) = hewan;
    cout << "Tindakan untuk " << hewan.nama << " (ID: " << hewan.id << ") telah dicatat ke riwayat." << endl;
}

Hewan pop(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Stack underflow! Riwayat kosong." << endl;
        Hewan kosong;
        kosong.id = -1;
        return kosong;
    }
    
    Hewan hewanDihapus = *(s -> riwayat + s -> top);
    s -> top--;
    return hewanDihapus;
}

void tampilkanRiwayat(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Riwayat tindakan kosong." << endl;
        return;
    }
    
    cout << "\n========== RIWAYAT TINDAKAN MEDIS ==========" << endl;
    tampilkanHeaderTabel();
    
    for (Hewan* ptr = s -> riwayat; ptr <= s -> riwayat + s -> top; ptr++) {
        cout << "| " << setw(5) << ptr -> id << " | " 
             << setw(15) << ptr -> nama << " | " 
             << setw(15) << ptr -> jenis << " | "
             << setw(10) << ptr -> pemilik << " | "
             << setw(15) << ptr -> keluhan << " | "
             << setw(12) << fixed << setprecision(0) << ptr -> harga << " |" << endl;
    }
    tampilkanFooterTabel();
    cout << "Total tindakan: " << (s -> top + 1) << endl;
}

void peekRiwayat(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Riwayat kosong." << endl;
        return;
    }
    
    Hewan* terakhir = s -> riwayat + s -> top;
    cout << "\n=== TINDAKAN TERAKHIR ===" << endl;
    cout << "ID      : " << terakhir -> id << endl;
    cout << "Nama    : " << terakhir -> nama << endl;
    cout << "Jenis   : " << terakhir -> jenis << endl;
    cout << "Pemilik : " << terakhir -> pemilik << endl;
    cout << "Keluhan : " << terakhir -> keluhan << endl;
    cout << "Harga   : Rp " << fixed << setprecision(0) << terakhir -> harga << endl;
}

void tambahHewan(Hewan* arr, int* n, const int& kapasitas) {
    cout << "========= TAMBAH HEWAN =========\n";

    if (*n >= kapasitas) {
        cout << "Kapasitas penuh! Tidak bisa menambah data.\n";
        return;
    }

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
        for (int i = 0; i < *n; i++) {
            if ((arr + i) -> id == inputID) {
                duplikat = true;
                break;
            }
        }

        if (duplikat) {
            cout << "ID sudah digunakan! Masukkan ID lain.\n";
        }

    } while (duplikat);

    (arr + *n) -> id = inputID;
    cin.ignore();

    (arr + *n) -> nama = inputTidakKosong("Masukkan Nama Hewan : ");
    (arr + *n) -> jenis = inputTidakKosong("Masukkan Jenis      : ");
    (arr + *n) -> pemilik = inputTidakKosong("Masukkan Nama Pemilik: ");
    (arr + *n) -> keluhan = inputTidakKosong("Masukkan Keluhan    : ");

    cout << "Masukkan Biaya      : ";
    while (!(cin >> (arr + *n) -> harga) || (arr + *n) -> harga < 0) {
        cout << "Biaya harus angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    (*n)++;
    cout << "\nData berhasil ditambahkan!" << endl;
}

void bubbleSortNama(Hewan* arr, int n) {
    cout << "========= SORT NAMA (A-Z) =========\n";

    for (int i = 0; i < n - 1; i++) {
        bool adaSwap = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j) -> nama > (arr + j + 1) -> nama) {
                swapHewan(arr + j, arr + j + 1);
                adaSwap = true;
            }
        }
        
        if (!adaSwap) break;
    }
    cout << "Sorting berhasil!\n";
}

void selectionSortHarga(Hewan* arr, int n) {
    cout << "========= SORT BIAYA TERMURAH =========\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            if ((arr + j) -> harga < (arr + minIdx) -> harga) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            swapHewan(arr + minIdx, arr + i); 
        }
    }
    cout << "Sorting berhasil!\n";
}

void sortByID(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j) -> id < (arr + minIdx) -> id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapHewan(arr + minIdx, arr + i);
        }
    }
}

void linearSearchNama(Hewan* arr, int n, string target) {
    cout << "\n========= LINEAR SEARCH =========\n";
    cout << "Mencari hewan dengan nama: " << target << endl;

    bool found = false;
    int jumlahDitemukan = 0;
    int indeksDitemukan[MAX];

    for (int i = 0; i < n; i++) {
        if ((arr + i) -> nama == target) {
            indeksDitemukan[jumlahDitemukan] = i;
            jumlahDitemukan++;
            found = true;
        }
    }

    if (found) {
        cout << "\nDitemukan " << jumlahDitemukan << " data:\n";
        
        for (int i = 0; i < jumlahDitemukan; i++) {
            if (indeksDitemukan[i] != i) {
                swapHewan(arr + indeksDitemukan[i], arr + i);
                for (int j = i + 1; j < jumlahDitemukan; j++) {
                    if (indeksDitemukan[j] == i) {
                        indeksDitemukan[j] = indeksDitemukan[i];
                        break;
                    }
                }
            }
        }
        
        tampilkanHeaderTabel();
        for (int i = 0; i < jumlahDitemukan; i++) {
            cout << "| " << setw(5) << (arr + i) -> id << " | " 
                 << setw(15) << (arr + i) -> nama << " | " 
                 << setw(15) << (arr + i) -> jenis << " | "
                 << setw(10) << (arr + i) -> pemilik << " | "
                 << setw(15) << (arr + i) -> keluhan << " | "
                 << setw(12) << (arr + i) -> harga << " |" << endl;
        }
        tampilkanFooterTabel();
    } else {
        cout << "\nData dengan nama '" << target << "' tidak ditemukan.\n";
    }
}

int minVal(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearchID(Hewan* arr, int n, int x) {
    cout << "\n========= FIBONACCI SEARCH =========\n";
    cout << "Mencari hewan dengan ID: " << x << endl;

    sortByID(arr, n);
    
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

    while (fibM > 1) {
        int i = minVal(offset + fibM2, n - 1);

        if ((arr + i) -> id < x) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if ((arr + i) -> id > x) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else {
            found = true;
            if (i != 0) swapHewan(arr + i, arr + 0);
            
            tampilkanHeaderTabel();
            cout << "| " << setw(5) << (arr + 0) -> id << " | "
                 << setw(15) << (arr + 0) -> nama << " | "
                 << setw(15) << (arr + 0) -> jenis << " | "
                 << setw(10) << (arr + 0) -> pemilik << " | "
                 << setw(15) << (arr + 0) -> keluhan << " | "
                 << setw(12) << (arr + 0) -> harga << " |" << endl;
            tampilkanFooterTabel();
            break;
        }
    }

    if (!found && fibM1 && (offset + 1 < n) && (arr + offset + 1) -> id == x) {
        found = true;
        if (offset + 1 != 0) swapHewan(arr + offset + 1, arr + 0);
        
        tampilkanHeaderTabel();
        cout << "| " << setw(5) << (arr + 0) -> id << " | "
             << setw(15) << (arr + 0) -> nama << " | "
             << setw(15) << (arr + 0) -> jenis << " | "
             << setw(10) << (arr + 0) -> pemilik << " | "
             << setw(15) << (arr + 0) -> keluhan << " | "
             << setw(12) << (arr + 0) -> harga << " |" << endl;
        tampilkanFooterTabel();
    }

    if (!found) {
        cout << "\nData dengan ID " << x << " tidak ditemukan.\n";
    }
}

Hewan* cariHewanByID(Hewan* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if ((arr + i) -> id == id) {
            return (arr + i);
        }
    }
    return nullptr;
}

int main() {
    const int KAPASITAS = 100;
    Hewan daftarHewan[KAPASITAS] = {
        {105, "Francis", "Kucing", 1500000, "Budi", "Demam"},
        {102, "Golden", "Anjing", 4500000, "Siti", "Muntah"},
        {108, "Winter", "Hamster", 50000, "Rina", "Luka"},
        {101, "Guana", "Reptil", 750000, "Andi", "Nafsu makan"},
        {104, "Noctua", "Burung", 2500000, "Dewi", "Bulu rontok"},
        {103, "Milo", "Kucing", 2000000, "Joko", "Batuk"},
        {107, "Bobby", "Anjing", 3500000, "Lisa", "Diare"},
        {106, "Kiki", "Burung", 500000, "Maya", "Mata berair"}
    };

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
                tambahHewan(daftarHewan, &jumlahHewan, KAPASITAS);
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
                linearSearchNama(daftarHewan, jumlahHewan, nama);
                break;
            }

            case 4: {
                cout << "========= CARI ID =========\n";
                int id;
                cout << "Masukkan ID Hewan: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                fibonacciSearchID(daftarHewan, jumlahHewan, id);
                break;
            }

            case 5:
                bubbleSortNama(daftarHewan, jumlahHewan);
                cout << "\nData setelah diurutkan berdasarkan Nama (A-Z):\n";
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 6:
                selectionSortHarga(daftarHewan, jumlahHewan);
                cout << "\nData setelah diurutkan berdasarkan Biaya (Termurah):\n";
                tampilkanData(daftarHewan, jumlahHewan);
                break;
                
            case 7: {
                cout << "========= TAMBAH PASIEN =========\n";
                if (isQueueFull(&antrian)) {
                    cout << "Queue overflow! Antrian sudah penuh!" << endl;
                    break;
                }
                
                int idHewan;
                cout << "Masukkan ID Hewan yang akan diantrikan: ";
                while (!(cin >> idHewan)) {
                    cout << "Input ID harus angka: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                Hewan* hewanDitemukan = cariHewanByID(daftarHewan, jumlahHewan, idHewan);
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
                cout << "========= TAMPILKAN RIWAYAT =========\n";
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

    return 0;
}