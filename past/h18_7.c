#include <stdio.h>

// --- グローバル変数と定数 ---
#define MAX_LENGTH 1000
int x[MAX_LENGTH];

// --- 関数のプロトタイプ宣言 ---
void B(int il, int m, int ir);
void A(int il, int ir);
void D(int il, int ir);
void print_array(const char* label, int n);


// --- 図7.1: マージ処理を行う関数B ---
void B(int il, int m, int ir) {
    int i, j, k;
    int temp[MAX_LENGTH];

    // マージ処理（xからtempへ）
    i = il;
    j = m + 1;
    for (k = il; k <= ir; k++) {
        if (i > m) {
            temp[k] = x[j++];
        } else if (j > ir) {
            temp[k] = x[i++];
        } else if (x[i] <= x[j]) {
            temp[k] = x[i++];
        } else {
            temp[k] = x[j++];
        }
    }
    // 結果のコピー（tempからxへ）
    for (k = il; k <= ir; k++) {
        x[k] = temp[k];
    }
}

// --- 図7.1: 再帰方式のマージソート関数A ---
void A(int il, int ir) {
    int m;

    if (il >= ir) return;
    m = (il + ir) / 2;
    A(il, m);
    A(m + 1, ir);
    B(il, m, ir);
}

// --- 図7.2: 非再帰方式のマージソート関数D ---
void D(int il, int ir) {
    int m, i, j, size;

    size = 1;
    while (size <= (ir - il)) {
        for (i = il; i <= ir; i = i + size * 2) {
            j = i + size * 2 - 1;
            m = (i + j) / 2;

            /*
             * 画像の空欄部分に相当する処理。
             * このままでは配列の境界外にアクセスする危険があるため、
             * 少なくともマージ対象の右半分が存在する場合にのみ
             * 実行するよう安全対策を施している。
             */
            if (m < ir) {
                // jが配列の末尾を超える場合は、末尾で切り詰める
                int end_j = (j > ir) ? ir : j;
                B(i, m, end_j);
            }
        }
        size = size * 2;
    }
}

// --- 配列表示用のヘルパー関数 ---
void print_array(const char* label, int n) {
    printf("%s", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}


// --- 実行とテストのためのmain関数 ---
int main() {
    printf("--- 関数A（再帰版）のテスト ---\n");
    int data_A[] = {9, 4, 3, 2, 8, 5, 1, 7};
    int n_A = sizeof(data_A) / sizeof(data_A[0]);
    for(int i=0; i<n_A; i++) x[i] = data_A[i];
    
    print_array("ソート前: ", n_A);
    A(0, n_A - 1);
    print_array("ソート後: ", n_A);
    
    printf("\n--- 関数D（非再帰版）のテスト ---\n");
    int data_D[] = {10, 7, 1, 5, 2, 9, 6, 3, 8, 4};
    int n_D = sizeof(data_D) / sizeof(data_D[0]);
    for(int i=0; i<n_D; i++) x[i] = data_D[i];

    print_array("ソート前: ", n_D);
    D(0, n_D - 1);
    print_array("ソート後: ", n_D);

    return 0;
}