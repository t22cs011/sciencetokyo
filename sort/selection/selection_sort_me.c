#include <stdio.h>

// 配列の要素を画面に出力する関数
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 選択ソート (Selection Sort)
void selection_sort(int a[], int n){
    int i, j, min_idx, tmp;
    // for(i = 0; i < n; i++){
    for(i = 0; i < n - 1; i++){
        min_idx = i;
        for(j = i + 1; j < n; j++){
            if(a[j] < a[min_idx]){
                min_idx = j;
            }
        }
        if(a[min_idx] < a[i]){ //swap
            tmp = a[min_idx];
            a[min_idx] = a[i];
            a[i] = tmp;
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


// void selection_sort(int a[], int n) {
//     int i, j, tmp;
//     for(int i = 0; i < n; i++){
//         int min_index = i;
//         for(int j = i + 1; j < n; j++){
//             if(a[j] < a[min_index]){
//                 min_index = j;
//             }
//         }
//         if(min_index != i){
//             tmp = a[min_index];
//             a[min_index] = a[i];
//             a[i] = tmp;
//         }
//     }
// }
