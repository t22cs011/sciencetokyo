#include <stdio.h>

// 配列の要素を画面に出力する関数
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// プログラム3.1: バブルソート (Bubble Sort)
void bubble_sort(int a[], int n) {
    int i, j, tmp;
    // n-1回、大きな値を配列の後方へ移動させる処理を繰り返す
    for (i = 0; i < n - 1; ++i) {
        // 配列の末尾からソート済み境界に向かって隣接要素を比較・交換する
        for (j = n - 1; i < j; --j) {
            if (a[j] < a[j-1]) {
                // a[j]の方が小さければ、前の要素と交換する
                tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
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

    // バブルソートを実行
    bubble_sort(data, n);

    // ソート後の配列を出力
    printf("ソート後の配列: ");
    print_array(data, n);

    return 0;
}