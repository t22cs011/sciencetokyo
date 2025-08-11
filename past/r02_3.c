#include <stdio.h>

// 関数のプロトタイプ宣言
void func1(int a[], int i, int j);
void func2(int a[], int m);
void func3(int a[], int m);
void swap(int a[], int i, int j);
void print_array(const char *label, int a[], int m);

int main() {
    // テスト用のデータ
    int a[] = {5, 2, 7, 3, 6, 1, 4}; 
    int m = sizeof(a) / sizeof(a[0]); // 配列の要素数

    print_array("Original array", a, m); // ソート前の配列を表示
    func3(a, m);                         // ヒープソートを実行
    print_array("Sorted array  ", a, m); // ソート後の配列を表示

    return 0;
}

// a[i]とa[j]の値を交換する
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// 配列の内容を表示する
void print_array(const char *label, int a[], int m) {
    printf("%s: ", label);
    for (int i = 0; i < m; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// MAX-HEAPIFY: iを根とする部分木を最大ヒープ化する
void func1(int a[], int i, int j) { // jはヒープの「最後の要素のインデックス」
    int k;
    while ((k = 2 * i + 1) <= j) {
        if (k < j && a[k] < a[k + 1]) {
            k++;
        }
        if (a[i] >= a[k]) {
            break;
        }
        swap(a, i, k);
        i = k;
    }
}

// BUILD-MAX-HEAP: 配列全体を最大ヒープに変換する
void func2(int a[], int m) {
    int i;
    for (i = m / 2 - 1; i >= 0; i--) {
        func1(a, i, m - 1);
    }
}

// HEAPSORT: ヒープソートの全工程を実行する
void func3(int a[], int m) {
    func2(a, m);

    while (m > 1) {
        swap(a, 0, m - 1);
        func1(a, 0, m - 2);
        m--;
    }
}