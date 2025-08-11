#include <stdio.h>

// 配列の要素を画面に出力する関数
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void insertion_sort(int a[], int n){
    int i, j, key;
    for(i = 1; i < n; i++){ // a[1]から開始
        j = i - 1; // 整列部分の末尾
        key = a[i]; //挿入する値(キー)を保持
        while(j >= 0 && a[j] > key){ //jが0以上で, かつキーより大きい場合後ろにずらす
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key; //キーを挿入 (j + 1となっているところに注意)
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

// void insertion_sort(int a[], int n) {
//     int i, j, key;
//     for(int i = 1; i < n; i++){
//         key = a[i];
//         int j = i - 1;
//         while(j >= 0 && a[j] > key){
//             a[j + 1] = a[j];
//             j--;
//         }
//         a[j + 1] = key;
//     }
// }