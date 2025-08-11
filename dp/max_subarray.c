#include <stdio.h>

// 共通のヘルパー関数
int max(int x, int y) {return x > y ? x : y;}

// カダネのアルゴリズム（最大部分配列の和と範囲を返す）
int max_subarray_with_range(int a[], int n, int *start, int *end) {
    if (n <= 0) return 0;
    
    int max_so_far = a[0];
    int max_ending_here = a[0];
    int temp_start = 0;
    *start = 0;
    *end = 0;
    
    for (int i = 1; i < n; i++) {
        if (max_ending_here + a[i] > a[i]) {
            max_ending_here = max_ending_here + a[i];
        } else {
            max_ending_here = a[i];
            temp_start = i;
        }
        
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            *start = temp_start;
            *end = i;
        }
    }
    
    return max_so_far;
}

// 元の関数（後方互換性のため）
int max_subarray(int a[], int n) {
    if (n <= 0) return 0;
    int t, s;
    t = s = a[0];
    for (int k = 1; k < n; k++) {
        t = max(t + a[k], a[k]);
        s = max(s, t);
    }
    return s;
}

// -----------------------------------------------------
// メイン関数 (各バージョンを実行して結果を比較)
// -----------------------------------------------------
int main() {
    // 問題文のサンプルデータ
    int a[] = {20, -24, 36, 3, -7, 27, -40, 37, -28, 6};
    int n = sizeof(a) / sizeof(a[0]);
    
    int start, end;
    int max_sum = max_subarray_with_range(a, n, &start, &end);
    
    printf("配列: ");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    
    printf("最大部分配列和: %d\n", max_sum);
    printf("最大部分配列の範囲: インデックス %d から %d\n", start, end);
    
    printf("最大部分配列: ");
    for (int i = start; i <= end; i++) {
        printf("%d", a[i]);
        if (i < end) printf(", ");
    }
    printf("\n");

    return 0;
}