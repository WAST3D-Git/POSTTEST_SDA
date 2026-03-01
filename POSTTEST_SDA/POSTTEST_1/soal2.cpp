#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int jumlah = 5;
    Mahasiswa mhs[jumlah];

    for (int i = 0; i < jumlah; i++) {
        cout << "Data Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama : "; getline(cin, mhs[i].nama);
        cout << "NIM  : "; getline(cin, mhs[i].nim);
        cout << "IPK  : "; cin >> mhs[i].ipk;
        cin.ignore();
        cout << endl;
    }

    int indeksTertinggi = 0;
    for (int i = 1; i < jumlah; i++) {
        if (mhs[i].ipk > mhs[indeksTertinggi].ipk) {
            indeksTertinggi = i;
        }
    }

    cout << "Mahasiswa dengan IPK Tertinggi:" << endl;
    cout << "Nama : " << mhs[indeksTertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeksTertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeksTertinggi].ipk << endl;

    return 0;
}