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
            // 置換コストrを設定 (一致:0, 不一致:3)
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
    // --- テスト ---
    char s3_1[] = "ABCDE";
    char s3_2[] = "CEADB";
    int dist = weighted_levenshtein(s3_1, s3_2, strlen(s3_1), strlen(s3_2));
    printf("--- Program 3.3: Weighted Levenshtein Distance ---\n");
    printf("s1: %s, s2: %s\n", s3_1, s3_2);
    printf("Distance (costs ins:2, del:2, sub:3): %d\n", dist);
    printf("(Note: Question b) asks for the value 'L'. Based on this code, L=%d)\n", dist);

    return 0;
}