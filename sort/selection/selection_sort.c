#include <stdio.h>

// 配列の要素を画面に出力する関数
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 2つのint型変数の値を交換する関数
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// 選択ソート (Selection Sort)
void selection_sort(int a[], int n) {
    int i, j, minj;
    for (i = 0; i < n - 1; ++i) {
        minj = i;
        for (j = i + 1; j < n; ++j) {
            if (a[j] < a[minj]) {
                minj = j;
            }
        }
        if (minj != i) {
            swap(&a[i], &a[minj]);
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

    // 選択ソートを実行
    selection_sort(data, n);

    // ソート後の配列を出力
    printf("ソート後の配列: ");
    print_array(data, n);

    return 0;
}
