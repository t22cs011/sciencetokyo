#include <stdio.h>

// プロトタイプ宣言
void heapify(int a[], int i, int j);
void build_heap(int a[], int m);
void heapsort(int a[], int m);
void swap(int a[], int i, int j);
void print_array(const char *label, int a[], int m);

// a[i]とa[j]の値を交換する
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


// MAX-HEAPIFY: "iを根とし、末尾がjである部分木"を最大ヒープ化する(iからjまでの部分木)
void heapify(int a[], int i, int j) { // jはヒープ(配列)のサイズ
    int k;
    while ((k = 2 * i + 1) <= j) { // (ア) kは左の子。子が存在する限りループ
        if (k < j && a[k] < a[k + 1]) { // (イ) もし右の子が存在し、かつ左の子より大きいなら
            k++; // kを右の子のインデックスにする
        }
        if (a[i] >= a[k]) { // 親が子以上の値を持っていればヒープ条件を満たす
            break; // ループを抜ける
        }
        swap(a, i, k); // 親と大きい方の子を交換
        i = k; // 次の比較対象を、交換した子の位置に移動
        // heapify(a, k, j);
    }
}

// BUILD-MAX-HEAP: 配列全体を最大ヒープに変換する
void build_heap(int a[], int m) {
    int i;
    for (i = m / 2 - 1; i >= 0; i--) { // 最後の非葉ノードから根に向かって実行
        heapify(a, i, m - 1); // 部分木をヒープ化
    }
}

// HEAPSORT: ヒープソートの全工程を実行する
void heapsort(int a[], int m) {
    build_heap(a, m); // 最初に配列全体をヒープ化

    while (m > 1) {
        swap(a, 0, m - 1); // 根（最大値）とヒープの末尾を交換
        heapify(a, 0, m - 2); // 縮小したヒープ(最後のインデックスはm-2)に対して再度ヒープ化を行う
        m--; // ヒープのサイズを1つ減らす
    }
}

// 配列の内容を表示する
void print_array(const char *label, int a[], int m) {
    printf("%s: ", label);
    for (int i = 0; i < m; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main() {
    int a[] = {5, 2, 7, 3, 6, 1, 4}; // テスト用のデータ
    int m = sizeof(a) / sizeof(a[0]); // 配列の要素数

    print_array("Original array", a, m); // ソート前の配列を表示

    heapsort(a, m); // ヒープソートを実行

    print_array("Sorted array  ", a, m); // ソート後の配列を表示

    return 0;
}
