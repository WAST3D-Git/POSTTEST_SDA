#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {
    int angka[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    int* ptr = angka;

    cout << "Array sebelum dibalik: \n";
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(ptr + i) << " | Alamat: " << (ptr + i) << endl;
    }

    reverseArray(angka, n);

    cout << "\nArray setelah dibalik: \n";
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(ptr + i) << " | Alamat: " << (ptr + i) << endl;
    }

    return 0;
}