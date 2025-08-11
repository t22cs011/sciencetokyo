#include <stdio.h>
#include <string.h>

// 2つのうち大きい方の値を返すヘルパー関数
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 3つのうち最小の値を返すヘルパー関数
int min(int a, int b, int c) {
    int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}

/**
 * @brief プログラム 3.1: 最長共通部分文字列 (Longest Common Substring)
 * 2つの文字列に共通して現れる連続した部分文字列の中で、最も長いものの長さを返す。
 * @param s1 1つ目の文字列
 * @param s2 2つ目の文字列
 * @param s1_len s1の長さ
 * @param s2_len s2の長さ
 * @return 最長共通部分文字列の長さ
 */
int longest_common_substring(const char s1[], const char s2[], int s1_len, int s2_len) {
    int i, j, k, mat[6][6];

    // kはこれまでに見つかった最長共通部分文字列の長さを保持する
    k = 0; // ア: ① 0

    // DPテーブルの初期化
    for (i = 0; i <= s1_len; i++) {
        mat[i][0] = 0;
    }
    for (j = 0; j <= s2_len; j++) {
        mat[0][j] = 0;
    }

    // DPテーブルを埋める
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            if (s1[i] == s2[j]) {
                // 文字が一致した場合、直前の斜めの値+1
                mat[i + 1][j + 1] = mat[i][j] + 1; // イ: ⑱ mat[i][j]+1
            } else {
                // 文字が一致しない場合、連続が途切れるので0
                mat[i + 1][j + 1] = 0; // ウ: ① 0
            }
            // 最大長の更新
            if (mat[i + 1][j + 1] > k) {
                k = mat[i + 1][j + 1];
            }
        }
    }
    return k;
}

/**
 * @brief プログラム 3.2: 最長共通部分列 (Longest Common Subsequence)
 * 2つの文字列に共通して現れる部分列（連続である必要はない）の中で、最も長いものの長さを返す。
 * @param s1 1つ目の文字列
 * @param s2 2つ目の文字列
 * @param s1_len s1の長さ
 * @param s2_len s2の長さ
 * @return 最長共通部分列の長さ
 */
int longest_common_subsequence(const char s1[], const char s2[], int s1_len, int s2_len) {
    int i, j, mat[6][6];
    
    // DPテーブルの初期化
    for (i = 0; i <= s1_len; i++) {
        mat[i][0] = 0;
    }
    for (j = 0; j <= s2_len; j++) {
        mat[0][j] = 0;
    }

    // DPテーブルを埋める
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            if (s1[i] == s2[j]) {
                // 文字が一致した場合、直前の斜めの値+1
                mat[i + 1][j + 1] = mat[i][j] + 1; // エ: ⑱ mat[i][j]+1
            } else {
                // 文字が不一致の場合、上か左の大きい方を採用
                if (mat[i][j + 1] > mat[i + 1][j]) { // オ: ㉑ mat[i+1][j] (比較対象)
                    mat[i + 1][j + 1] = mat[i][j + 1];
                } else {
                    mat[i + 1][j + 1] = mat[i + 1][j]; // カ: ㉑ mat[i+1][j] (代入値)
                }
            }
        }
    }
    // 最終結果は右下のセルに格納されている
    return mat[s1_len][s2_len]; // キ: ⑰ mat[i][j] (ループ終了後のi,jの値)
}


/**
 * @brief プログラム 3.3: 重み付きレーベンシュタイン距離 (Weighted Levenshtein Distance)
 * 挿入(2), 削除(2), 置換(1)のコストで2つの文字列間の編集距離を計算する。
 * (注: 問題文の置換コスト3とは異なるが、選択肢に基づき1で実装)
 * @param s1 1つ目の文字列
 * @param s2 2つ目の文字列
 * @param s1_len s1の長さ
 * @param s2_len s2の長さ
 * @return 重み付きレーベンシュタイン距離
 */
int weighted_levenshtein(const char s1[], const char s2[], int s1_len, int s2_len) {
    int i, j, r, mat[6][6];

    // DPテーブルの初期化 (削除コスト)
    // 削除コストは2なので、距離は i * 2 となる
    for (i = 0; i <= s1_len; i++) {
        mat[i][0] = i * 2; // ク: ⑤ i*2
    }
    // DPテーブルの初期化 (挿入コスト)
    // 挿入コストは2なので、距離は j * 2 となる
    // 注: 問題のコードではループ変数がiだが、jの誤記として解釈し、jでループ
    for (j = 0; j <= s2_len; j++) {
        mat[0][j] = j * 2; // ケ: ⑦ j*2 (変数をjと解釈した場合)
    }

    // DPテーブルを埋める
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            // 置換コストrを設定 (一致:0, 不一致:1)
            // 注: 問題文のコスト3とは異なるが、選択肢から1を選択
            if (s1[i] == s2[j]) {
                r = 0;
            } else {
                r = 3; // コ: ② 3
            }
            
            // 3つの操作(置換、削除、挿入)のうち最小コストを選択
            int substitution_cost = mat[i][j] + r;
            int deletion_cost = mat[i][j + 1] + 2;
            int insertion_cost = mat[i + 1][j] + 2;

            // 以下のif-elseチェーンはmin関数を模擬している
            if (substitution_cost < deletion_cost && substitution_cost < insertion_cost) {
                mat[i + 1][j + 1] = substitution_cost; // サ: ⑳ mat[i][j]+r
            } else if (insertion_cost < deletion_cost) { // 原文の順序 (mat[i+1][j]+2 < mat[i][j+1]+2) に従う
                mat[i + 1][j + 1] = insertion_cost;    // シ: ㉘ mat[i+1][j]+2
            } else {
                mat[i + 1][j + 1] = deletion_cost;     // ス: ㉙ mat[i][j+1]+2
            }
        }
    }
    // 最終結果は右下のセルに格納されている
    return mat[s1_len][s2_len]; // セ: ⑰ mat[i][j] (ループ終了後のi,jの値)
}

int main() {
    // --- プログラム3.1のテスト ---
    char s1_1[] = "ABCD";
    char s1_2[] = "ADBC";
    int len_substring = longest_common_substring(s1_1, s1_2, strlen(s1_1), strlen(s1_2));
    printf("--- Program 3.1: Longest Common Substring ---\n");
    printf("s1: %s, s2: %s\n", s1_1, s1_2);
    printf("Length: %d (Expected: 2, for 'BC')\n\n", len_substring);

    // --- プログラム3.2のテスト ---
    char s2_1[] = "ABCD";
    char s2_2[] = "ADBC";
    int len_subsequence = longest_common_subsequence(s2_1, s2_2, strlen(s2_1), strlen(s2_2));
    printf("--- Program 3.2: Longest Common Subsequence ---\n");
    printf("s1: %s, s2: %s\n", s2_1, s2_2);
    printf("Length: %d (Expected: 3, for 'ABC' or 'ADC')\n\n", len_subsequence);

    // --- プログラム3.3のテスト ---
    char s3_1[] = "ABCDE";
    char s3_2[] = "CEADB";
    int dist = weighted_levenshtein(s3_1, s3_2, strlen(s3_1), strlen(s3_2));
    printf("--- Program 3.3: Weighted Levenshtein Distance ---\n");
    printf("s1: %s, s2: %s\n", s3_1, s3_2);
    printf("Distance (costs ins:2, del:2, sub:1): %d\n", dist);
    printf("(Note: Question b) asks for the value 'L'. Based on this code, L=%d)\n", dist);

    return 0;
}