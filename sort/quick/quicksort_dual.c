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


void quicksort_dual(int a[], int low, int high) {
    if (low >= high) {
        return;
    }

    // --- ここからがパーティション処理 ---
    // ステップ1: 2つのピボット p1, p2 を決定 (p1 <= p2)
    if (a[low] > a[high]) {
        swap(&a[low], &a[high]);
    }
    int p1 = a[low];
    int p2 = a[high];

    // ステップ2: ポインタを初期化
    int lt = low + 1;   // p1未満の領域の右端
    int gt = high - 1;  // p2より大きい領域の左端
    int k = low + 1;    // 現在調査中のポインタ

    // ステップ3: 配列を3つの領域に分割
    while (k <= gt) {
        if (a[k] < p1) {
            // p1より小さい場合、lt領域と交換
            swap(&a[k], &a[lt]);
            lt++;
        } 
        else if (a[k] > p2) {
            // p2より大きい場合、gt領域と交換
            // kはインクリメントしない（交換してきた要素を再評価するため）
            swap(&a[k], &a[gt]);
            gt--;
            continue; // kをインクリメントせずにループの先頭へ
        }
        k++;
    }

    // ステップ4: ピボットを正しい位置に配置
    lt--;
    gt++;
    swap(&a[low], &a[lt]);
    swap(&a[high], &a[gt]);
    // --- パーティション処理ここまで ---

    // 3つの領域をそれぞれ再帰的にソート
    quicksort_dual(a, low, lt - 1);
    quicksort_dual(a, lt + 1, gt - 1);
    quicksort_dual(a, gt + 1, high);
}

int main() {   // カウンターをリセット
    // --- クイックソート(Hoare 両方からpivot) ---
    int c[] = {9, 8, 5, 1, 2};
    int n = 5;

    printf("クイックソート前: ");
    print_array("c", c, n);

    quicksort_dual(c, 0, n - 1);
    
    printf("クイックソート後: ");
    print_array("c", c, n);

    return 0;
}