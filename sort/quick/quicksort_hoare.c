#include <stdio.h>


// 配列の内容を出力するヘルパー関数
void print_array(const char *name, int a[], int n) {
    printf("%s: {", name);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// int partition(int a[], int low, int high){
//     int i = low;
//     int j = high - 1;
//     int pivot = a[high];

//     while(i <= j){
//         while(a[i] < pivot)
//             i++;
//         while(a[j] >= pivot)
//             j--;
//         if(i < j)
//             swap(&a[i], &a[j]);
//     }
//     swap(&a[i], &a[high]);
//     return j;
// }

/**
 * Hoare（ホーア）方式のパーティション分割を行う関数
 * @param arr   対象の配列
 * @param low   パーティション範囲の下限インデックス
 * @param high  パーティション範囲の上限インデックス
 * @return      分割点を返す
 */
int partition(int arr[], int low, int high) {
    // 1. 先頭の要素をピボットとして選択
    int pivot = arr[high];
    
    // 2. ポインタを範囲の外側から開始
    int i = low - 1;
    int j = high + 1;

    while (1) {
        // 3. 左から、ピボット以上の値を持つ要素を探す
        do {
            i++;
        } while (arr[i] < pivot);

        // 4. 右から、ピボット以下の値を持つ要素を探す
        do {
            j--;
        } while (arr[j] > pivot);

        // 5. ポインタが交差したら、jを分割点としてループを終了
        if (i >= j) {
            return j;
        }

        // 6. ポインタが交差していなければ、見つけた要素同士を交換
        swap(&arr[i], &arr[j]);
    }
}

void quick_sort(int a[], int low, int high){
    if(low < high){
        int p = partition(a, low, high);
        quick_sort(a, low, p);
        quick_sort(a, p + 1, high);
    }
}

void sort_array(int a[], int low, int high){
    return quick_sort(a, 0, high);
}


int main() {   // カウンターをリセット
    // --- クイックソート(Hoare 両方からpivot) ---
    int c[] = {9, 8, 5, 1, 2};
    int n = 5;

    printf("クイックソート前: ");
    print_array("c", c, n);

    sort_array(c, 0, n - 1);
    
    printf("クイックソート後: ");
    print_array("c", c, n);

    return 0;
}