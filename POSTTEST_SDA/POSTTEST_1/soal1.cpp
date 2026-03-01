#include <iostream>
#include <vector>
using namespace std;

void FindMin(int A[], int n) {
    int min = A[0];
    int index = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            index = i;
        }
    }

    cout << "Nilai Minimum : " << min << endl;
    cout << "Indeks        : " << index << endl;
}

int main() {
    int fibonacci[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    FindMin(fibonacci, n);

    return 0;
}


/*
 * Hasil Analisis:
   * 1. Best Case (Kasus Terbaik): Terjadi jika elemen pertama A adalah elemen terkecil. 
        Kondisi (A[i] < min) selalu bernilai false, sehingga  operasi assignment 'min = A[i]' tidak pernah dieksekusi.
        T(n) = 4n + 2 => Big-O: O(n).

   * 2. Worst Case (Kasus Terburuk): Terjadi jika array terurut menurun (descending), 
        sehingga setiap iterasi menemukan nilai yang lebih kecil. Kondisi (A[i] < min) selalu true. 
        T(n) = 5n + 1 => Big-O: O(n).
 */