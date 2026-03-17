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
    cout << "\n" << setfill('=') << setw(63) << "" << endl;
    cout << setfill(' ');
    cout << "| " << setw(5) << "ID" << " | " 
         << setw(15) << "Nama Hewan" << " | " 
         << setw(15) << "Jenis" << " | " 
         << setw(15) << "Harga (Rp)" << " |" << endl;
    cout << setfill('=') << setw(63) << "" << endl;
}

void tampilkanFooterTabel() {
    cout << setfill('-') << setw(63) << "" << endl;
    cout << setfill(' ');
}

void tampilkanData(Hewan* ptr, int n) {
    if (n == 0) {
        cout << "Data masih kosong!" << endl;
        return;
    }

    tampilkanHeaderTabel();

    for (int i = 0; i < n; i++) {
        cout << setfill(' ') << right;
        cout << "| " << setw(5) << (ptr + i)->id << " | " 
             << setw(15) << (ptr + i)->nama << " | " 
             << setw(15) << (ptr + i)->jenis << " | " 
             << setw(15) << fixed << setprecision(0) << (ptr + i)->harga << " |" << endl;
    }

    tampilkanFooterTabel();
}

void tambahHewan(Hewan* arr, int& n) {
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
        for (int i = 0; i < n; i++) {
            if (arr[i].id == inputID) {
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

    cout << "Masukkan Harga      : ";
    while (!(cin >> (arr + n)->harga) || (arr + n)->harga < 0) {
        cout << "Harga harus angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    n++;
    cout << "\nData berhasil ditambahkan!" << endl;
}

void bubbleSortNama(Hewan* arr, int n) {
    cout << "========= SORT NAMA (A-Z) =========\n";

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama)
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void selectionSortHarga(Hewan* arr, int n) {
    cout << "========= SORT HARGA TERMURAH =========\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[minIdx].harga)
                minIdx = j;
        }
        swap(&arr[minIdx], &arr[i]);
    }
}

void linearSearchNama(Hewan* arr, int n, string target) {
    bool found = false;

    for (int i = 0; i < n; i++) {
        if ((arr + i)->nama == target) {
            if (!found) tampilkanHeaderTabel();
            cout << setfill(' ') << right;
            cout << "| " << setw(5) << (arr + i)->id << " | " 
                 << setw(15) << (arr + i)->nama << " | " 
                 << setw(15) << (arr + i)->jenis << " | " 
                 << setw(15) << (arr + i)->harga << " |" << endl;

            found = true;
        }
    }

    if (found) tampilkanFooterTabel();
    else cout << "\nData tidak ditemukan.\n";
}

int minVal(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearchID(Hewan* arr, int n, int x) {
    cout << "\n========= PROSES FIBONACCI SEARCH =========\n";

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id)
                swap(&arr[j], &arr[j + 1]);
        }
    }

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

    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);

        cout << "\nIterasi ke-" << iterasi++ << endl;
        cout << "fibM = " << fibM 
             << ", fibM1 = " << fibM1 
             << ", fibM2 = " << fibM2 << endl;
        cout << "offset = " << offset << endl;
        cout << "Index yang dicek = " << i << endl;
        cout << "Nilai ID = " << arr[i].id << endl;

        if (arr[i].id < x) {
            cout << "Keputusan: " << arr[i].id << " < " << x << " --> geser ke kanan\n";

            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if (arr[i].id > x) {
            cout << "Keputusan: " << arr[i].id << " > " << x << " <-- geser ke kiri\n";

            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else {
            cout << "Keputusan: DATA DITEMUKAN!\n";

            tampilkanHeaderTabel();
            cout << setfill(' ') << right;
            cout << "| " << setw(5) << arr[i].id << " | "
                 << setw(15) << arr[i].nama << " | "
                 << setw(15) << arr[i].jenis << " | "
                 << setw(15) << arr[i].harga << " |" << endl;
            tampilkanFooterTabel();
            return;
        }
    }

    if (fibM1 && (offset + 1 < n) && arr[offset + 1].id == x) {
        cout << "\nPengecekan terakhir di index " << offset + 1 << endl;
        cout << "Keputusan: DATA DITEMUKAN!\n";

        tampilkanHeaderTabel();
        cout << "| " << setw(5) << arr[offset + 1].id << " | "
             << setw(15) << arr[offset + 1].nama << " | "
             << setw(15) << arr[offset + 1].jenis << " | "
             << setw(15) << arr[offset + 1].harga << " |" << endl;
        tampilkanFooterTabel();
        return;
    }

    cout << "\nKesimpulan: Data dengan ID " << x << " tidak ditemukan.\n";
}

int main() {
    Hewan daftarHewan[100] = {
        {105, "Francis", "Kucing", 1500000},
        {102, "Golden", "Anjing", 4500000},
        {108, "Winter", "Hamster", 50000},
        {101, "Guana", "Reptil", 750000},
        {104, "Noctua", "Burung", 2500000}
    };

    int jumlahHewan = 5;
    int pilihan;

    do {
        system("cls||clear");

        cout << "======= PAWCARE PETSHOP =======" << endl;
        cout << "1. Tambahkan Hewan\n";
        cout << "2. Tampilkan Semua Hewan\n";
        cout << "3. Cari Berdasarkan Nama\n";
        cout << "4. Cari Berdasarkan ID\n";
        cout << "5. Urutkan Berdasarkan Nama (A-Z)\n";
        cout << "6. Urutkan Berdasarkan Harga (Termurah)\n";
        cout << "7. Keluar\n";

        cout << "Pilih Menu: ";
        while (!(cin >> pilihan)) {
            cout << "Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        system("cls||clear");

        switch (pilihan) {
            case 1:
                tambahHewan(daftarHewan, jumlahHewan);
                break;

            case 2:
                cout << "========= DATA HEWAN =========\n";
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 3: {
                cout << "========= CARI NAMA =========\n";
                cin.ignore();
                string nama = inputTidakKosong("Nama: ");
                linearSearchNama(daftarHewan, jumlahHewan, nama);
                break;
            }

            case 4: {
                cout << "========= CARI ID =========\n";
                int id;
                cout << "ID: ";
                cin >> id;
                fibonacciSearchID(daftarHewan, jumlahHewan, id);
                break;
            }

            case 5:
                bubbleSortNama(daftarHewan, jumlahHewan);
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 6:
                selectionSortHarga(daftarHewan, jumlahHewan);
                tampilkanData(daftarHewan, jumlahHewan);
                break;

            case 7:
                cout << "Terima kasih!\n";
                break;
        }

        if (pilihan != 7) {
            system("pause");
        }

    } while (pilihan != 7);

    return 0;
}