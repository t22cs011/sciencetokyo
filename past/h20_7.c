#include <stdio.h>

// comp関数の呼び出し回数をカウントするグローバル変数
int comp_count = 0;

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

int comp(int a, int b) {
    // 関数が呼ばれたのでカウンターをインクリメント
    comp_count++;
    if (a < b) {
        return 1;
    } else {
        return 0;
    }
}

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

// バブルソート
void sort1(int a[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (comp(a[j], a[j - 1])) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
}

// クイックソートのパーティション分割
int partition(int a[], int l, int r) {
    int i, j, pv;
    i = l - 1;
    j = r;
    pv = a[r];
    while (1) {
        while (comp(a[++i], pv));
        // 短絡評価を考慮した条件
        while (i < j && comp(pv, a[--j]));
        if (i >= j) {
            break;
        }
        swap(&a[i], &a[j]);
    }
    swap(&a[i], &a[r]);
    return i;
}

// クイックソート（再帰部分）
void sort2_i(int a[], int l, int r) {
    int v;
    if (l >= r) {
        return;
    }
    v = partition(a, l, r);
    sort2_i(a, l, v - 1);
    sort2_i(a, v + 1, r);
}

// クイックソート（初期呼び出し）
void sort2(int a[], int n) {
    sort2_i(a, 0, n - 1);
}

int main() {
    // --- 問題1の検証 ---
    printf("## 問題1 (sort1: バブルソート) の検証\n");
    int b[] = {13, 9, 6, 1, 4};
    int n_b = 5;

    printf("ソート前: ");
    print_array("b", b, n_b);

    // カウンターをリセット
    comp_count = 0;
    sort1(b, n_b);

    printf("ソート後: ");
    print_array("b", b, n_b);
    printf("-> sort1でのcomp呼び出し回数: %d\n", comp_count);

    printf("\n----------------------------------------\n\n");

    // --- 問題4の検証 ---
    printf("## 問題4 (sort2: クイックソート) の検証\n");
    int c[] = {9, 8, 5, 1, 2};
    int n_c = 5;

    printf("ソート前: ");
    print_array("c", c, n_c);

    // カウンターをリセット
    comp_count = 0;
    sort2(c, n_c);
    
    printf("ソート後: ");
    print_array("c", c, n_c);
    printf("-> sort2でのcomp呼び出し回数: %d\n", comp_count);

    return 0;
}