#include <stdio.h>

// 配列の要素を画面に出力する関数
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// プログラム3.2: 挿入ソート (Insertion Sort)
void insertion_sort(int a[], int n) {
    int i, j, tmp;
    for (j = 1; j < n; ++j) {
        tmp = a[j];
        i = j - 1;
        while (0 <= i && tmp < a[i]) {
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = tmp;
    }
}

int main() {
    // ソート対象の配列を定義
    int data[] = {8, 4, 3, 7, 6, 1, 2, 5};
    
    // 配列の要素数を計算
    int n = sizeof(data) / sizeof(data[0]);

    // ソート前の配列を出力
    printf("ソート前の配列: ");
    print_array(data, n);

    // 挿入ソートを実行
    insertion_sort(data, n);

    // ソート後の配列を出力
    printf("ソート後の配列: ");
    print_array(data, n);

    return 0;
}