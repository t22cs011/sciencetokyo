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
    for(int i = 0; i < n; i++){
        for(int j = n - 1; j > i; j--){
            if(a[j] < a[j - 1]){
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
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



// int i, j, tmp;
// for(int i = 0; i < n; i++){
//     for(int j = n - 1; j > i; j--){
//         if(a[j - 1] > a[j]){
//             tmp = a[j];
//             a[j] = a[j - 1];
//             a[j - 1] = tmp;
//         }
//     }
// }