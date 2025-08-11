// Dual-Pivot Quicksort
// 2つのピボットを使い、配列を [<p1], [p1<=x<=p2], [>p2] の3つに分割する

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

// 3-Way Quicksort
// 配列を [< pivot], [== pivot], [> pivot] の3つに分割する
void quick_sort_3way(int a[], int low, int high) {
    if (low >= high) {
        return;
    }

    // --- パーティション処理 ---
    int pivot = a[low]; // 先頭をピボットに
    int lt = low;       // 'less than'領域の右端
    int gt = high;      // 'greater than'領域の左端
    int i = low + 1;    // 現在調査中のポインタ

    while (i <= gt) {
        if (a[i] < pivot) {
            // ピボットより小さい場合、lt領域と交換
            swap(&a[lt], &a[i]);
            lt++;
            i++;
        } else if (a[i] > pivot) {
            // ピボットより大きい場合、gt領域と交換
            swap(&a[i], &a[gt]);
            gt--;
        } else { // a[i] == pivot
            // ピボットと等しい場合、iを進めるだけ
            i++;
        }
    }
    // --- パーティション処理ここまで ---

    // 左右の領域（< pivot と > pivot）を再帰的にソート
    quick_sort_3way(a, low, lt - 1);
    quick_sort_3way(a, gt + 1, high);
}


int main() {   // カウンターをリセット
    // --- クイックソート(Hoare 両方からpivot) ---
    int c[] = {9, 8, 5, 1, 2};
    int n = 5;

    printf("クイックソート前: ");
    print_array("c", c, n);

    quick_sort_3way(c, 0, n - 1);
    
    printf("クイックソート後: ");
    print_array("c", c, n);

    return 0;
}