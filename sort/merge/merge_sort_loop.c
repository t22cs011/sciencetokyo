#include <stdio.h>

// 配列の要素をきれいに表示するためのヘルパー関数
void print_array(const char* label, int arr[], int size) {
    printf("%s: [ ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

/**
 * @brief 2つのソート済み部分配列をマージする関数
 */
void merge(int a[], int begin, int mid, int end, int w[]) {
    int i = begin;
    int j = mid + 1;
    int k;

    // [マージ] ソート済みの左右の配列(a)を、作業配列(w)にマージする
    for (k = begin; k <= end; k++) {
        if (i > mid) {
            w[k] = a[j++];
        } else if (j > end) {
            w[k] = a[i++];
        } else if (a[i] <= a[j]) {
            w[k] = a[i++];
        } else {
            w[k] = a[j++];
        }
    }

    // [コピー] マージ結果を作業配列(w)から元の配列(a)に書き戻す
    for (k = begin; k <= end; k++) {
        a[k] = w[k];
    }
}

/**
 * @brief 画像のロジックに合わせたボトムアップ（非再帰）マージソート
 */
void mergesort_loop(int a[], int n, int w[]) {
    int il = 0;
    int ir = n - 1;
    int m, i, j, size;

    size = 1;
    while (size <= (ir - il)) {
        for (i = il; i <= ir; i = i + size * 2) {
            // 画像の計算方法に準拠
            j = i + size * 2 - 1;
            m = (i + j) / 2;

            //--- 境界チェック（安全な実行に必須）---
            if (m >= ir) {
                break; // マージするペアの右側が存在しない
            }
            if (j > ir) {
                j = ir; // マージ範囲の終点が配列の末尾を超えないように調整
            }
            //-------------------------------------

            // 画像の空欄に相当するマージ処理の呼び出し
            merge(a, i, m, j, w);
        }
        size = size * 2;
    }
}


int main() {
    int a[] = {3, 5, 1, 4, 2, 8, 6, 7};
    int n = sizeof(a) / sizeof(a[0]);
    int w[n];

    print_array("Before", a, n);

    // 作成した関数を呼び出す
    mergesort_loop(a, n, w);

    print_array("After ", a, n);

    return 0;
}