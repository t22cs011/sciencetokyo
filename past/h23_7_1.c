#include <stdio.h>

// グローバル配列 (各行のクイーンの位置を格納)
// 静的記憶域期間を持つため、要素はすべて0で初期化される
int a[1024];

// 配列aの内容をカンマ区切りで出力する関数
void printa(int n) {
    int i;
    if (n > 0) {
        printf("%d", a[0]);
    }
    for (i = 1; i < n; i++) {
        printf(", %d", a[i]);
    }
    printf("\n");
}

// (x, y) に要素を配置可能かチェックする関数
// この実装では、同じ値 (行) が既に使用されているかのみを調べる
int check(int x, int y) {
    int k;
    for (k = 0; k < x; k++) {
        if (a[k] == y) {
            return 0; // 使用済みのため配置不可
        }
    }
    return 1; // 配置可能
}

// 順列を生成するための再帰関数
void f(int n, int x) {
    // printa(n); // 元のコードの位置
    if (x == n) {
        // 解が一つ見つかったので出力する
        printa(n);
        return;
    }

    for (int y = 0; y < n; y++) {
        if (check(x, y)) {
            a[x] = y;       // yをx番目に配置
            f(n, x + 1);    // 次の要素を決めるために再帰呼び出し
        }
    }
}

// メイン関数
int main(void) {
    // n=3, 開始位置x=0で関数fを呼び出す
    f(3, 0);
    return 0;
}