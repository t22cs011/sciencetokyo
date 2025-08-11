#include <stdio.h>
#include <string.h>

// 2つの整数のうち大きい方を返すヘルパー関数
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 最長共通部分列 (Longest-Common Subsequence) の長さを求める関数
int longest_common_subsequence(char s1[], char s2[], int s1_len, int s2_len) {
    int i, j;
    // 文字列長が5以下とされているため、mat[6][6]で十分
    // mat[i][j]は s1のi文字目までとs2のj文字目までのLCS長を格納
    int mat[6][6]; 

    // 配列の0行目と0列目を0で初期化
    for (i = 0; i <= s1_len; i++) {
        mat[i][0] = 0;
    }
    for (j = 0; j <= s2_len; j++) {
        mat[0][j] = 0;
    }

    // 動的計画法に基づきテーブルを埋める
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            // ケース1: 末尾の文字が一致する場合
            if (s1[i] == s2[j]) {
                // エ: 左斜め上の値 + 1
                mat[i + 1][j + 1] = mat[i][j] + 1;
            } 
            // ケース2: 末尾の文字が一致しない場合
            else {
                // オ, カ: 上の値と左の値を比較し、大きい方を採用
                mat[i + 1][j + 1] = max(mat[i][j + 1], mat[i + 1][j]);
            }
        }
    }
    
    // キ: テーブルの右下の値が最終的な解となる
    return mat[s1_len][s2_len];
}

// プログラムの実行を開始するmain関数
int main() {
    char s1[] = "ABCD";
    char s2[] = "ADBC";
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);

    // longest_common_subsequence関数を呼び出し、結果を表示する
    int result = longest_common_subsequence(s1, s2, s1_len, s2_len);
    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("最長共通部分列の長さ: %d\n", result); // "ABC"の長さである3が出力される

    return 0;
}
