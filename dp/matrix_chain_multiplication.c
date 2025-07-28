#include <stdio.h>
#include <limits.h> // INT_MAX を使用するため

// --- 再帰による解法 (Recursive Approach) ---

/**
 * @brief 行列連鎖 Ai...Aj の最小乗算回数を再帰的に計算する
 * @param p 行列の次元を格納した配列 (p[i-1] x p[i] が行列Aiのサイズ)
 * @param i 計算対象の開始インデックス
 * @param j 計算対象の終了インデックス
 * @return 最小乗算回数
 */
int solve_recursive(int p[], int i, int j) {
    // ベースケース: 行列が1つの場合、乗算は不要
    if (i == j) {
        return 0;
    }

    int min_cost = INT_MAX;

    // kは分割位置 (Ai...Ak) と (Ak+1...Aj)
    for (int k = i; k < j; k++) {
        // 再帰的に部分問題のコストを計算し、今回の分割コストを加算する
        int cost = solve_recursive(p, i, k) +
                   solve_recursive(p, k + 1, j) +
                   // [ 空欄 A ] に対応:
                   // (Ai...Ak)の結果(p[i-1] x p[k])と(Ak+1...Aj)の結果(p[k] x p[j])の乗算コスト
                   p[i - 1] * p[k] * p[j];
        
        if (cost < min_cost) {
            min_cost = cost;
        }
    }
    return min_cost;
}

// --- 動的計画法による解法 (Dynamic Programming Approach) ---

/**
 * @brief 行列連鎖 A1...An の最小乗算回数を動的計画法で計算する
 * @param p 行列の次元を格納した配列
 * @param n 行列の数
 * @return 最小乗算回数
 */
int solve_dp(int p[], int n) {
    // dp[i][j] は行列連鎖 Ai...Aj の最小乗算回数を格納
    // 配列サイズは n+1 x n+1 とし、1-based indexでアクセスする
    int dp[n + 1][n + 1];

    // 長さ1の連鎖 (行列1つ) のコストは0
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    // len は計算対象の行列連鎖の長さ (2からnまで)
    for (int len = 2; len <= n; len++) {
        // i は連鎖の開始インデックス
        // [ 空欄 B ] に対応: jがnを超えないように、iのループ範囲を設定
        for (int i = 1; i <= n - len + 1; i++) {
            // j は連鎖の終了インデックス
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            // k は連鎖の分割位置
            for (int k = i; k < j; k++) {
                // [ 空欄 C ] に対応: p[j]
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    // [ 空欄 D ] に対応: 最終的な解は A1...An のコスト
    return dp[1][n];
}


// --- メイン関数 (動作確認用) ---
int main() {
    // 問題の例: A1(10x30), A2(30x5), A3(5x60)
    // p = {10, 30, 5, 60}
    int p[] = {10, 30, 5, 60};
    // 行列の数nは、配列pのサイズ-1
    int n = sizeof(p) / sizeof(p[0]) - 1;

    printf("行列の次元配列 p = {10, 30, 5, 60}\n");
    printf("行列の数: %d\n\n", n);

    printf("--- 解法 --- \n");
    // 再帰解の呼び出し (A1...A3の計算なので、i=1, j=3)
    printf("再帰による解法: %d\n", solve_recursive(p, 1, n));
    
    // DP解の呼び出し
    printf("動的計画法による解法: %d\n", solve_dp(p, n));

    printf("\n--- 別の例 --- \n");
    int p2[] = {40, 20, 30, 10, 30};
    int n2 = sizeof(p2) / sizeof(p2[0]) - 1;
    printf("行列の次元配列 p2 = {40, 20, 30, 10, 30}\n");
    printf("行列の数: %d\n\n", n2);
    printf("再帰による解法: %d\n", solve_recursive(p2, 1, n2));
    printf("動的計画法による解法: %d\n", solve_dp(p2, n2));


    return 0;
}
