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

    for (int i = 0; i < n - 1; i++) {
        bool adaSwap = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nama > (arr + j + 1)->nama) {
                swap(arr + j, arr + j + 1);
                adaSwap = true;
            }
        }
        
        if (!adaSwap) {
            break;
        }
    }
    cout << "\nSorting berhasil!\n";
}

void selectionSortHarga(Hewan* arr, int n) {
    cout << "========= SORT BIAYA TERMURAH =========\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            swap(arr + minIdx, arr + i);
        }
    }
    cout << "\nSorting berhasil!\n";
}

void sortByID(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->id < (arr + minIdx)->id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr + minIdx, arr + i);
        }
    }
}

void linearSearchNama(Hewan* arr, int n, string target) {
    cout << "\n========= PROSES LINEAR SEARCH =========\n";
    cout << "Mencari hewan dengan nama: " << target << endl;

    bool found = false;
    int jumlahDitemukan = 0;
    int indeksDitemukan[100]; 

    for (int i = 0; i < n; i++) {
        if ((arr + i)->nama == target) {
            indeksDitemukan[jumlahDitemukan] = i;
            jumlahDitemukan++;
            found = true;
        }
    }

    if (found) {
        cout << "\nMenampilkan data yang ditemukan:\n";
        
        for (int i = 0; i < jumlahDitemukan; i++) {
            if (indeksDitemukan[i] != i) {
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

    // Step 1: Mengurutkan data berdasarkan ID
    sortByID(arr, n);
    
    // Step 2: Melakukan Fibonacci Search
    // Inisialisasi bilangan Fibonacci: fibM2 = F(k-2), fibM1 = F(k-1), fibM = F(k)
    int fibM2 = 0;               // Elemen ke (k-2) dalam deret Fibonacci
    int fibM1 = 1;               // Elemen ke (k-1) dalam deret Fibonacci
    int fibM = fibM2 + fibM1;    // Elemen ke (k) = F(k-2) + F(k-1)

    // Mencari bilangan Fibonacci terkecil yang >= n
    // Algoritma: terus maju dalam deret Fibonacci hingga fibM >= n
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    int offset = -1;    // Offset untuk menandai batas kiri yang sudah diperiksa
    bool found = false;

    // Proses pencarian utama
    // Loop berlanjut selama fibM > 1, artinya masih ada elemen yang bisa diperiksa
    while (fibM > 1) {
        /*Menentukan indeks yang akan diperiksa
          Mengambil nilai minimum antara (offset + fibM2) dan (n-1)
          offset + fibM2 adalah posisi yang membagi array dengan rasio Fibonacci*/
        int i = minVal(offset + fibM2, n - 1);

        // Jika nilai di index i kurang dari target, geser ke kanan, artinya target berada di bagian kanan dari index i
        if ((arr + i)->id < x) {
            // Update nilai Fibonacci untuk pencarian di bagian kanan
            fibM = fibM1;           // Fibonacci bergeser ke bawah
            fibM1 = fibM2;          // Update fibM1 menjadi nilai sebelumnya
            fibM2 = fibM - fibM1;   // Hitung fibM2 baru
            offset = i;             // Update offset untuk menandai batas kiri baru
        }

        // Jika nilai di index i lebih besar dari target, geser ke kiri, artinya target berada di bagian kiri dari index i
        else if ((arr + i)->id > x) {
            // Update nilai Fibonacci untuk pencarian di bagian kiri
            fibM = fibM2;           // FibM menjadi fibM2 untuk pencarian kiri
            fibM1 = fibM1 - fibM2;  // Update fibM1
            fibM2 = fibM - fibM1;   // Hitung fibM2 baru
        }

        // Jika ditemukan kecocokan
        else {
            found = true;
            
            // Menukar data yang ditemukan ke posisi pertama
            if (i != 0) {
                swap(arr + i, arr + 0);  // Sesuai ketentuan "Setiap searching dan pointer menerapkan swap dengan pointer"
            }

            // Menampilkan data yang ditemukan
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

    // Pengecekan terakhir: jika fibM1 masih ada dan elemen terakhir yang belum diperiksa, periksa apakah itu target
    if (!found && fibM1 && (offset + 1 < n) && (arr + offset + 1)->id == x) {
        found = true;
        
        // Menukar data yang ditemukan ke posisi pertama
        if (offset + 1 != 0) {
            swap(arr + offset + 1, arr + 0); 
        }

        // Menampilkan data yang ditemukan
        tampilkanHeaderTabel();
        cout << "| " << setw(5) << (arr + 0)->id << " | "
             << setw(15) << (arr + 0)->nama << " | "
             << setw(15) << (arr + 0)->jenis << " | "
             << setw(10) << (arr + 0)->pemilik << " | "
             << setw(15) << (arr + 0)->keluhan << " | "
             << setw(12) << (arr + 0)->harga << " |" << endl;
        tampilkanFooterTabel();
    }

    // Jika data tidak ditemukan setelah semua pemeriksaan
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