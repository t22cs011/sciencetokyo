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
 * @brief 配列をマージソートで並べ替え、要素の比較回数を返す関数
 * @param a ソート対象の配列
 * @param begin ソート範囲の開始インデックス
 * @param end ソート範囲の終了インデックス
 * @param w マージ処理用の一時作業配列
 * @return 要素の比較回数
 */
int mergesort(int a[], int begin, int end, int w[]) {
    // 【変更点①】 ベースケース: ソート範囲の要素が1つ以下なら比較は0回
    if (begin >= end) {
        return 0;
    }

    // 【変更点②】 この関数スコープでの比較回数を数えるカウンターを宣言
    int c = 0;
    int mid = (begin + end) / 2;

    // 1. 分割: 前半と後半をそれぞれ再帰的にソート
    // 【変更点③】 再帰呼び出しが返した比較回数を c に格納・加算していく
    c = mergesort(a, begin, mid, w);      // 左半分の比較回数を取得
    // c += mergesort(a, mid + 1, end, w);   // 右半分の比較回数を加算

    // 2. 統治 (マージ処理)
    int i = begin;
    int j = mid + 1;
    int k;

    // [マージ] ソート済みの左右の配列(a)を、作業配列(w)にマージする
    for (k = begin; k <= end; k++) {
        if (i > mid) {
            w[k] = a[j++];
        } else if (j > end) {
            w[k] = a[i++];
        } else {
            // 【変更点④】 実際に左右の要素を比較する際にカウンターを増やす
            // c++;
            if (a[i] <= a[j]) {
                w[k] = a[i++];
            } else {
                w[k] = a[j++];
            }
        }
    }

    // [コピー] マージ結果を作業配列(w)から元の配列(a)に書き戻す
    for (k = begin; k <= end; k++) {
        a[k] = w[k];
    }

    // 【変更点⑤】 このスコープで集計した総比較回数を返す
    return 0;
    // return c;
}

int main() {
    int a[] = {3, 5, 1, 4, 2};
    int n = sizeof(a) / sizeof(a[0]);
    int w[n];

    print_array("Before", a, n);

    // マージソートを実行し、比較回数を受け取る
    int count = mergesort(a, 0, n - 1, w);

    print_array("After ", a, n);
    printf("Comparisons: %d\n", count); // 比較回数を表示

    return 0;
}