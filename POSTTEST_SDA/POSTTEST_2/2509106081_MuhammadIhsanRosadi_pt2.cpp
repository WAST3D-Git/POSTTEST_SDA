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
            cout << "Input tidak boleh kosong!\n";
        }

    } while (input.empty() || hanyaSpasi);

    return input;
}

void swap(Hewan* a, Hewan* b) {
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
        cout << setfill(' ') << right;
        cout << "| " << setw(5) << (arr + i)->id << " | " 
             << setw(15) << (arr + i)->nama << " | " 
             << setw(15) << (arr + i)->jenis << " | "
             << setw(10) << (arr + i)->pemilik << " | "
             << setw(15) << (arr + i)->keluhan << " | "
             << setw(12) << fixed << setprecision(0) << (arr + i)->harga << " |" << endl;
    }

    tampilkanFooterTabel();
}

void tambahHewan(Hewan*& arr, int& n, const int& kapasitas) {
    cout << "========= TAMBAH HEWAN =========\n";

    if (n >= kapasitas) {
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
        for (int i = 0; i < n; i++) {
            if ((arr + i)->id == inputID) {
                duplikat = true;
                break;
            }
        }

        if (duplikat) {
            cout << "ID sudah digunakan! Masukkan ID lain.\n";
        }

    } while (duplikat);

    (arr + n)->id = inputID;
    cin.ignore();

    (arr + n)->nama = inputTidakKosong("Masukkan Nama Hewan : ");
    (arr + n)->jenis = inputTidakKosong("Masukkan Jenis      : ");
    (arr + n)->pemilik = inputTidakKosong("Masukkan Nama Pemilik: ");
    (arr + n)->keluhan = inputTidakKosong("Masukkan Keluhan    : ");

    cout << "Masukkan Biaya      : ";
    while (!(cin >> (arr + n)->harga) || (arr + n)->harga < 0) {
        cout << "Biaya harus angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    n++;
    cout << "\nData berhasil ditambahkan!" << endl;
}

void bubbleSortNama(Hewan* arr, int n) {
    cout << "========= SORT NAMA (A-Z) =========\n";
    cout << "Proses Bubble Sort dengan swap pointer:\n";

    for (int i = 0; i < n - 1; i++) {
        bool adaSwap = false;
        cout << "\nIterasi ke-" << i+1 << ":\n";
        
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nama > (arr + j + 1)->nama) {
                cout << "  Swap: " << (arr + j)->nama << " dengan " << (arr + j + 1)->nama << endl;
                swap(arr + j, arr + j + 1);
                adaSwap = true;
            }
        }
        
        if (!adaSwap) {
            cout << "  Tidak ada swap, data sudah terurut.\n";
            break;
        }
    }
    cout << "\nSorting selesai!\n";
}

void selectionSortHarga(Hewan* arr, int n) {
    cout << "========= SORT BIAYA TERMURAH =========\n";
    cout << "Proses Selection Sort dengan swap pointer:\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        cout << "\nIterasi ke-" << i+1 << ":\n";
        cout << "  Mencari harga termurah dari index " << i << " hingga " << n-1 << endl;
        
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            cout << "  Swap: Harga " << (arr + i)->harga << " (index " << i 
                 << ") dengan " << (arr + minIdx)->harga << " (index " << minIdx << ")" << endl;
            swap(arr + minIdx, arr + i);
        } else {
            cout << "  Tidak ada swap, posisi sudah benar.\n";
        }
    }
    cout << "\nSorting selesai!\n";
}

void swapElement(Hewan* arr, int pos1, int pos2) {
    if (pos1 != pos2) {
        cout << "  Swap: data index " << pos1 << " dengan index " << pos2 << endl;
        swap(arr + pos1, arr + pos2);
    }
}

void sortByID(Hewan* arr, int n) {
    cout << "\n--- Mengurutkan data berdasarkan ID (untuk persiapan Fibonacci Search) ---\n";
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->id < (arr + minIdx)->id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            cout << "  Swap ID: " << (arr + i)->id << " dengan " << (arr + minIdx)->id << endl;
            swap(arr + minIdx, arr + i);
        }
    }
}

void linearSearchNama(Hewan* arr, int n, string target) {
    cout << "\n========= PROSES LINEAR SEARCH =========\n";
    cout << "Mencari hewan dengan nama: " << target << endl;
    cout << "Proses Linear Search dengan pointer:\n\n";

    bool found = false;
    int jumlahDitemukan = 0;
    int indeksDitemukan[100]; 

    for (int i = 0; i < n; i++) {
        cout << "  Memeriksa index " << i << ": " << (arr + i)->nama;
        
        if ((arr + i)->nama == target) {
            cout << " -> DITEMUKAN!" << endl;
            indeksDitemukan[jumlahDitemukan] = i;
            jumlahDitemukan++;
            found = true;
        } else {
            cout << " -> bukan target" << endl;
        }
    }

    if (found) {
        cout << "\nMenampilkan data yang ditemukan:\n";
        
        for (int i = 0; i < jumlahDitemukan; i++) {
            if (indeksDitemukan[i] != i) {
                cout << "  Menukar data dari index " << indeksDitemukan[i] << " ke index " << i << endl;
                swap(arr + indeksDitemukan[i], arr + i);
            
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
            cout << setfill(' ') << right;
            cout << "| " << setw(5) << (arr + i)->id << " | " 
                 << setw(15) << (arr + i)->nama << " | " 
                 << setw(15) << (arr + i)->jenis << " | "
                 << setw(10) << (arr + i)->pemilik << " | "
                 << setw(15) << (arr + i)->keluhan << " | "
                 << setw(12) << (arr + i)->harga << " |" << endl;
        }
        tampilkanFooterTabel();
        
        cout << "\nDitemukan " << jumlahDitemukan << " data dengan nama '" << target << "'\n";
    } else {
        cout << "\nData dengan nama '" << target << "' tidak ditemukan.\n";
    }
}

int minVal(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearchID(Hewan* arr, int n, int x) {
    cout << "\n========= PROSES FIBONACCI SEARCH =========\n";
    cout << "Mencari hewan dengan ID: " << x << endl;

    cout << "\nTahap 1: Mengurutkan data berdasarkan ID (menggunakan swap):\n";
    sortByID(arr, n);
    
    cout << "\nTahap 2: Melakukan Fibonacci Search:\n";

    int fibM2 = 0;
    int fibM1 = 1; 
    int fibM = fibM2 + fibM1;

    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    cout << "\nInisialisasi Fibonacci:\n";
    cout << "fibM = " << fibM << ", fibM1 = " << fibM1 << ", fibM2 = " << fibM2 << endl;

    int offset = -1;
    int iterasi = 1;
    bool found = false;

    while (fibM > 1) {
        int i = minVal(offset + fibM2, n - 1);

        cout << "\nIterasi ke-" << iterasi++ << endl;
        cout << "fibM = " << fibM 
             << ", fibM1 = " << fibM1 
             << ", fibM2 = " << fibM2 << endl;
        cout << "offset = " << offset << endl;
        cout << "Index yang dicek = " << i << endl;
        cout << "Nilai ID = " << (arr + i)->id << endl;

        if ((arr + i)->id < x) {
            cout << "Keputusan: " << (arr + i)->id << " < " << x << " --> geser ke kanan\n";

            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if ((arr + i)->id > x) {
            cout << "Keputusan: " << (arr + i)->id << " > " << x << " <-- geser ke kiri\n";

            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else {
            cout << "Keputusan: DATA DITEMUKAN pada index " << i << "!\n";
            found = true;
            
            if (i != 0) {
                cout << "\nTahap 3: Menukar data yang ditemukan ke posisi pertama:\n";
                cout << "  Swap index " << i << " dengan index 0" << endl;
                swap(arr + i, arr + 0);
            }

            tampilkanHeaderTabel();
            cout << setfill(' ') << right;
            cout << "| " << setw(5) << (arr + 0)->id << " | "
                 << setw(15) << (arr + 0)->nama << " | "
                 << setw(15) << (arr + 0)->jenis << " | "
                 << setw(10) << (arr + 0)->pemilik << " | "
                 << setw(15) << (arr + 0)->keluhan << " | "
                 << setw(12) << (arr + 0)->harga << " |" << endl;
            tampilkanFooterTabel();
            break;
        }
    }

    if (!found && fibM1 && (offset + 1 < n) && (arr + offset + 1)->id == x) {
        cout << "\nPengecekan terakhir di index " << offset + 1 << endl;
        cout << "Keputusan: DATA DITEMUKAN pada index " << offset + 1 << "!\n";

        if (offset + 1 != 0) {
            cout << "\nTahap 3: Menukar data yang ditemukan ke posisi pertama:\n";
            cout << "  Swap index " << offset + 1 << " dengan index 0" << endl;
            swap(arr + offset + 1, arr + 0);
        }

        tampilkanHeaderTabel();
        cout << "| " << setw(5) << (arr + 0)->id << " | "
             << setw(15) << (arr + 0)->nama << " | "
             << setw(15) << (arr + 0)->jenis << " | "
             << setw(10) << (arr + 0)->pemilik << " | "
             << setw(15) << (arr + 0)->keluhan << " | "
             << setw(12) << (arr + 0)->harga << " |" << endl;
        tampilkanFooterTabel();
        found = true;
    }

    if (!found) {
        cout << "\nKesimpulan: Data dengan ID " << x << " tidak ditemukan.\n";
    }
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

    do {
        system("cls||clear");

        cout << "======= PAWCARE PETSHOP & DOKTER HEWAN =======" << endl;
        cout << "1. Tambahkan Hewan\n";
        cout << "2. Tampilkan Semua Hewan\n";
        cout << "3. Cari Berdasarkan Nama (Linear)\n";
        cout << "4. Cari Berdasarkan ID (Fibonacci)\n";
        cout << "5. Urutkan Berdasarkan Nama (Bubble)\n";
        cout << "6. Urutkan Berdasarkan Harga (Selection)\n";
        cout << "7. Keluar\n";

        cout << "Pilih Menu: ";
        while (!(cin >> pilihan)) {
            cout << "Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        system("cls||clear");

        switch (pilihan) {
            case 1: {
                Hewan* ptrHewan = daftarHewan;
                tambahHewan(ptrHewan, jumlahHewan, KAPASITAS);
                break;
            }

            case 2:
                cout << "========= DATA HEWAN PAWCARE =========\n";
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 3: {
                cout << "========= CARI NAMA (LINEAR) =========\n";
                cin.ignore();
                string nama = inputTidakKosong("Masukkan Nama Hewan: ");
                linearSearchNama(daftarHewan, jumlahHewan, nama);
                break;
            }

            case 4: {
                cout << "========= CARI ID (FIBONACCI) =========\n";
                int id;
                cout << "Masukkan ID Hewan: ";
                cin >> id;
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

            case 7:
                cout << "Terima kasih telah menggunakan Pawcare Petshop!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }

        if (pilihan != 7) {
            cout << "\n";
            system("pause");
        }

    } while (pilihan != 7);

    return 0;
}