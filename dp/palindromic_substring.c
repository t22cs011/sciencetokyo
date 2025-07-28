#include <stdio.h>
#include <string.h>

// --- 単純な方法 (Naive Approach) ---

/**
 * @brief 部分文字列 s[i...j] が回文かを判定する
 * @param s 対象の文字列
 * @param i 開始インデックス
 * @param j 終了インデックス
 * @return 回文なら1、そうでなければ0
 */
int is_palindrome(char* s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) {
            return 0; // 回文ではない
        }
        i++;
        j--;
    }
    return 1; // 回文である
}

/**
 * @brief 最長回文部分文字列の長さをナイーブな方法で計算する
 * 計算量: O(n^3)
 * @param s 対象の文字列
 * @return 最長の長さ
 */
int solve_naive(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;
    
    int max_len = 1; // 長さ1の文字はすべて回文
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (is_palindrome(s, i, j)) {
                // [ 空欄 A ] に対応: 部分文字列の長さは j - i + 1
                int current_len = j - i + 1;
                if (max_len < current_len) {
                    max_len = current_len;
                }
            }
        }
    }
    return max_len;
}

// --- 動的計画法を用いた方法 (Dynamic Programming Approach) ---

/**
 * @brief 最長回文部分文字列の長さを動的計画法で計算する
 * 計算量: O(n^2)
 * @param s 対象の文字列
 * @return 最長の長さ
 */
int solve_dp(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;

    // dp[i][j] は s[i...j] が回文なら1、そうでなければ0
    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    int max_len = 1;

    // 長さ1の文字列はすべて回文
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // 長さ2以上の部分文字列をチェック
    // len: これからチェックする部分文字列の長さ
    for (int len = 2; len <= n; len++) {
        // i: 部分文字列の開始インデックス
        // [ 空欄 B ] に対応: jがnを超えないように、iのループ範囲を設定
        for (int i = 0; i <= n - len; i++) {
            // j: 部分文字列の終了インデックス
            int j = i + len - 1;

            // [ 空欄 C ], [ 空欄 D ] に対応:
            // 両端の文字が一致し、かつその内側の部分文字列が回文であるかチェック
            if (s[i] == s[j] && (len == 2 || dp[i + 1][j - 1] == 1)) {
                dp[i][j] = 1;
                if (max_len < len) {
                    max_len = len;
                }
            }
        }
    }
    return max_len;
}


// --- メイン関数 (動作確認用) ---
int main() {
    char test_str1[] = "babad";
    char test_str2[] = "cbbd";
    char test_str3[] = "abacaba";

    printf("--- Test Case 1: \"%s\" ---\n", test_str1);
    printf("Naive Solution: %d\n", solve_naive(test_str1));
    printf("DP Solution:    %d\n", solve_dp(test_str1));
    printf("\n");

    printf("--- Test Case 2: \"%s\" ---\n", test_str2);
    printf("Naive Solution: %d\n", solve_naive(test_str2));
    printf("DP Solution:    %d\n", solve_dp(test_str2));
    printf("\n");
    
    printf("--- Test Case 3: \"%s\" ---\n", test_str3);
    printf("Naive Solution: %d\n", solve_naive(test_str3));
    printf("DP Solution:    %d\n", solve_dp(test_str3));
    printf("\n");

    return 0;
}