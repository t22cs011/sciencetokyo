#include <stdio.h>
#include <stdlib.h>

// LISの長さと、その部分列自体を求める関数
int find_lis(int arr[], int n, int** lis_sequence) {
    if (n == 0) {
        *lis_sequence = NULL;
        return 0;
    }

    int* dp = (int*)malloc(n * sizeof(int)); // dp[i] は arr[i] で終わる最長増加部分列の長さを格納する
    int* prev = (int*)malloc(n * sizeof(int)); // prev[i] は arr[i] で終わるLISの前の要素のインデックスを格納する

    for (int i = 0; i < n; i++) { // 全ての要素はそれ自身が長さ1の増加部分列であるため、1で初期化する
        dp[i] = 1;
        prev[i] = -1; // prevは前の要素がないことを示す-1で初期化する
    }

    for (int i = 1; i < n; i++) { // dpテーブルをボトムアップで埋めていく
        for (int j = 0; j < i; j++) { // この二重ループがアルゴリズムの核である
            if (arr[j] < arr[i]) { // arr[i] より小さい要素 arr[j] が見つかった場合
                if (dp[i] < 1 + dp[j]) { // arr[j]で終わるLISにarr[i]を繋げた方が長くなるなら更新
                    dp[i] = 1 + dp[j];
                    prev[i] = j; // 経路を記録
                }
            }
        }
    }

    int max_len = 0; // dpテーブルからLISの長さ(最大値)とその最後の要素のインデックスを見つける
    int last_index = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
            last_index = i;
        }
    }

    *lis_sequence = (int*)malloc(max_len * sizeof(int)); // LISの実際の部分列を復元する
    int current_index = last_index;
    for (int i = max_len - 1; i >= 0; i--) { // 後ろから詰めていくことで、正しい順序の部分列を得る
        (*lis_sequence)[i] = arr[current_index];
        current_index = prev[current_index];
    }

    free(dp); // 動的に確保したメモリを解放
    free(prev);

    return max_len;
}

int main() {
    int arr[] = {5, 2, 8, 6, 3, 6, 9, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int* lis_seq = NULL;
    int length = find_lis(arr, n, &lis_seq);

    printf("元の配列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("最長増加部分列 (LIS) の長さ: %d\n", length);
    printf("LIS: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", lis_seq[i]);
    }
    printf("\n");

    free(lis_seq); // 復元した部分列のために確保したメモリを解放

    return 0;
}