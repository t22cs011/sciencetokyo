#include <stdio.h>
#include <stdlib.h> // abs()関数を使用するために必要

#define N 8 // Nクイーン問題のサイズ (自由に変更可能)

// クイーンの位置を格納するグローバル配列
int a[N];

/**
 * @brief 解を出力する関数
 * @param n ボードのサイズ
 */
void printa(int n) {
    // 解が見つかったことを示すヘッダー
    printf("Solution found: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // チェスボード形式での可視化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] == j) {
                printf("Q "); // クイーンの位置
            } else {
                printf(". "); // 空のマス
            }
        }
        printf("\n");
    }
    printf("----------------\n");
}

/**
 * @brief (x, y)にクイーンを配置可能かチェックする関数
 * @param x 現在の列 (column)
 * @param y 現在の行 (row)
 * @return 1なら配置可能, 0なら配置不可
 */
int check(int x, int y) {
    int k;
    // xより前の列に配置されたクイーンとの衝突をチェック
    for (k = 0; k < x; k++) {
        // [C] 水平方向のチェック と [D] 斜め方向のチェック
        if (a[k] == y || abs(a[k] - y) == x - k) {
            return 0; // 衝突するため配置不可
        }
    }
    return 1; // 安全なため配置可能
}

/**
 * @brief Nクイーン問題の解を列挙する関数 (非再帰版)
 * @param n ボードのサイズ
 * @param x_start 探索を開始する列 (通常は0)
 */
void f(int n, int x_start) {
    int x = x_start;
    int y = 0;

    // while(1)は無限ループを意味し、gotoで制御する
    while (1) {
        // 現在のx列で、y行目からクイーンを置ける場所を探す
        while (y < n) {
            if (check(x, y)) {
                // 配置可能な場合
                a[x] = y;   // (x, y) にクイーンを配置
                x = x + 1;  // 次の列へ進む

                if (x >= n) {
                    // 全ての列に配置完了 (解が一つ見つかった)
                    printa(n);
                    goto backtrack; // 解を出力後、バックトラックして別の解を探す
                }

                // [E] 次の列の探索は0行目から開始
                y = 0;
            } else {
                // 配置不可の場合、同じ列の次の行を試す
                y = y + 1;
            }
        } // 内側のwhileループ終了 (x列目に置ける場所がなかった)

    backtrack: // バックトラック処理の開始点
        x = x - 1; // 一つ前の列に戻る
        if (x < 0) {
            // 最初の列より前に戻ったら探索終了
            return;
        }

        // [F] 前の列で探索を再開するのは、前回置いた場所の次の行から
        y = a[x] + 1;
    }
}

/**
 * @brief メイン関数 (プログラムの実行開始点)
 */
int main(void) {
    printf("Starting %d-Queens solver...\n\n", N);
    // Nクイーン問題を0列目から解き始める
    f(N, 0);
    printf("\nAll solutions have been found.\n");
    return 0;
}