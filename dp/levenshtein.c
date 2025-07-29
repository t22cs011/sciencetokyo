#include <stdio.h>
#include <string.h>

/**
 * @brief 2つの文字列間の重み付きレーベンシュタイン距離を計算する。
 * (コスト: 削除=2, 挿入=2, 置換=1)
 * @param s1 1つ目の文字列
 * @param s2 2つ目の文字列
 * @param s1_len s1の長さ
 * @param s2_len s2の長さ
 * @return int 重み付きレーベンシュタイン距離
 */
int Levenshtein(char s1[], char s2[], int s1_len, int s2_len) {
    int i, j, r, mat[6][6];

    // 削除コストの初期化
    for (i = 0; i < s1_len + 1; i++) {
        mat[i][0] = i * 2; // ク: ⑥
    }

    // 挿入コストの初期化 (注: ループ変数がi)
    for (i = 0; i < s2_len + 1; i++) {
        mat[0][i] = i * 2; // ケ: ⑥
    }

    // DPテーブルの充填
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            // 置換コストrを設定
            if (s1[i] == s2[j]) {
                r = 0;
            } else {
                r = 3; // コ: ②
            }

            // 3つの操作(置換/一致、削除、挿入)のうち最小コストを選択
            if (mat[i][j] + r < mat[i][j + 1] + 2 && mat[i][j] + r < mat[i + 1][j] + 2) {
                mat[i + 1][j + 1] = mat[i][j] + r; // サ: ⑳
            } else if (mat[i][j + 1] + 2 < mat[i + 1][j] + 2) {
                mat[i + 1][j + 1] = mat[i][j + 1] + 2; // シ: ㉓
            } else {
                mat[i + 1][j + 1] = mat[i + 1][j] + 2; // ス: ㉗
            }
        }
    }

    // ループ終了後のi,jはそれぞれs1_len, s2_lenとなるため、mat[s1_len][s2_len]を返す
    return mat[i][j]; // セ: ⑰
}

// --- 実行用メイン関数 ---
int main() {
    char s1[] = "ABCDE";
    char s2[] = "CEADB";
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // 画像のコードは固定長の配列 mat[6][6] を使用しているため、
    // 文字列長が5以下の場合にのみ正しく動作する
    if (len1 > 5 || len2 > 5) {
        printf("Error: String length must be 5 or less.\n");
        return 1;
    }

    int distance = Levenshtein(s1, s2, len1, len2);

    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("Levenshtein Distance: %d\n", distance);

    return 0;
}