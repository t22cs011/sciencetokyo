#include <stdio.h>
#include <string.h>

// --- グローバル変数と定数 ---
#define MAX_I 50   // iの最大値 (要素数)
#define MAX_S 100  // jまたはsの最大値 (目標の和)

// 問題で与えられた値
int a[] = {8, 2, 4};
int n = 3;
int k; // kの値はmain関数内で設定する

// メモ化再帰/動的計画法で使用するテーブル
int b[MAX_I][MAX_S];


// --- 1. 単純な再帰関数 (問1の図3.1) ---
// 関数名を f に変更
int f(int s, int i) {
    // ベースケース: 全ての要素をチェックし終えた
    if (i == n) {
        // 現在の和sが目標のkと一致すれば1 (成功)、しなければ0 (失敗)を返す
        return s == k;
    }

    // a[i]を選ばない場合 + a[i]を選ぶ場合の組み合わせの総和を返す
    int res = f(s, i + 1) + f(s + a[i], i + 1);
    return res;
}


// --- 2. メモ化再帰関数 (問2の改善版) ---
// 関数名を f_memo に変更
int f_memo(int s, int i) {
    // ベースケース: 全ての要素をチェックし終えた
    if (i == n) {
        return s == k;
    }
    
    // 計算済みの場合はその結果を返す
    if (b[i][s] != -1) {
        return b[i][s];
    }

    // 未計算の場合、再帰的に計算して結果をテーブルに保存する
    int res = f_memo(s, i + 1) + f_memo(s + a[i], i + 1);
    
    return b[i][s] = res; // 計算結果を保存して返す
}


// --- 3. 動的計画法 (DP) 関数 (問3の図3.2) ---
// 関数名を g に変更
int g(void) {
    int i, j;
    // DPテーブルを0で初期化
    memset(b, 0, sizeof(b));

    // DPループ
    for (i = 0; i < n; i++) {
        for (j = 0; j <= k; j++) {
            
            // [③]に対応するロジック: if (j == 0)
            // 和が0は何も選ばなければ常に達成可能。
            if (j == 0) {
                b[i][j] = 1;
                continue; // このjのループはここで終わり
            }
            
            // i=0 (最初の要素) の場合
            if (i == 0) {
                if (j == a[i]) b[i][j] = 1;
                continue; // このjのループはここで終わり
            }
            
            // i>0 (2番目以降の要素) の場合
            
            // [④]に対応するロジック: if (b[i-1][j])
            // a[i]を使わない場合。前の行(i-1)の結果を引き継ぐ。
            if (b[i-1][j]) {
                b[i][j] = 1;
            }
            
            // [⑤]に対応するロジック: if (b[i-1][j - a[i]])
            // a[i]を使う場合。
            if (j >= a[i]) {
                if (b[i-1][j - a[i]]) {
                    b[i][j] = 1;
                }
            }
        }
    }
    
    // 最終結果: a[0]からa[n-1]までを使って和kが作れるか
    return b[n-1][k];
}


// --- main関数 ---
int main(void) {
    printf("--- 部分和問題の3つの解法 ---\n");
    printf("集合 A = {8, 2, 4}, n = 3\n\n");

    // 問1: 単純な再帰 (k=7)
    k = 7;
    printf("1. 単純な再帰 (関数f, k=%d)\n", k);
    printf("   結果: %d\n\n", f(0, 0));

    // 問2: メモ化再帰 (k=7)
    k = 7;
    // メモ化テーブルを-1で初期化
    memset(b, -1, sizeof(b)); 
    printf("2. メモ化再帰 (関数f_memo, k=%d)\n", k);
    printf("   結果: %d\n\n", f_memo(0, 0));

    // 問3: 動的計画法 (k=6)
    k = 6;
    printf("3. 動的計画法 (関数g, k=%d)\n", k);
    printf("   結果: %d\n\n", g());

    return 0;
}