#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    cout << "Masukkan nilai pertama: "; cin >> x;
    cout << "Masukkan nilai kedua: "; cin >> y;

    cout << "\nSebelum pertukaran:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    swap(&x, &y);

    cout << "\nSesudah pertukaran:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    return 0;
}