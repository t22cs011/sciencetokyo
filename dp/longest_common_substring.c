#include <stdio.h>
#include <string.h>

// 最長共通部分文字列の長さを求める関数
int longest_common_substring(char s1[], char s2[], int s1_len, int s2_len) {
    int i, j, k;
    // 文字列長が5以下とされているため、mat[6][6]で十分
    int mat[6][6]; 

    // 配列の0行目と0列目を初期化
    for (i = 0; i < s1_len + 1; i++) {
        mat[i][0] = 0;
    }
    for (i = 0; i < s2_len + 1; i++) {
        mat[0][i] = 0;
    }

    k = 0; // ア: 最大長の初期化
    for (i = 0; i < s1_len; i++) {
        for (j = 0; j < s2_len; j++) {
            if (s1[i] == s2[j]) {
                // イ: 文字が一致した場合、直前の長さに1を加える
                mat[i + 1][j + 1] = mat[i][j] + 1;
                //計算した長さ mat[i+1][j+1] が、それまでの最大長 k より大きければ、k を更新
                if (mat[i + 1][j + 1] > k) {
                    k = mat[i + 1][j + 1];
                }
            } else {
                // ウ: 文字が一致しない場合、長さを0にリセット
                mat[i + 1][j + 1] = 0;
            }
        }
    }
    return k;
}

// プログラムの実行を開始するmain関数
int main() {
    char s1[] = "ABCD";
    char s2[] = "ADBC";
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);

    // longest_common_substring関数を呼び出し、結果を表示する
    int result = longest_common_substring(s1, s2, s1_len, s2_len);
    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("最長共通部分文字列の長さ: %d\n", result); // "BC"の長さである2が出力される

    return 0;
}