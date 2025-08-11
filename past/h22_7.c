#include <stdio.h>

// 定数定義 (comb3の配列サイズ)
#define MAXARG 100

// --- 関数プロトタイプ宣言 ---
int comb1(int n, int k);
int comb2(int n, int k);
int comb3(int n, int k);
int pf(int m, int n);

// --- main関数 ---
int main() {
    int n = 10;
    int k = 5;

    // nやkが大きすぎるとcomb1の計算に時間がかかりすぎるため注意
    if (n > 25) {
        printf("nの値が大きすぎるため、comb1の実行をスキップします。\n");
    } else {
        printf("comb1(%d, %d) = %d  (再帰による計算)\n", n, k, comb1(n, k));
    }

    printf("comb2(%d, %d) = %d  (公式による計算)\n", n, k, comb2(n, k));
    printf("comb3(%d, %d) = %d  (動的計画法による計算)\n", n, k, comb3(n, k));

    return 0;
}

/**
 * @brief comb1: 再帰的な定義で組み合わせを計算する
 * nCk = (n-1)Ck + (n-1)C(k-1)
 * 長所: コードが簡潔で、定義が直感的
 * 短所: 重複計算が多く、nが大きくなると極端に遅くなる。スタックオーバーフローの危険性。
 */
int comb1(int n, int k) {
    if (k < 0 || k > n) {
        return 0; // 不正な引数
    }
    if (k == 0 || k == n) {
        return 1; // 基底条件
    }
    if (k > n / 2) {
        k = n - k; // 計算量を減らすための最適化
    }
    return comb1(n - 1, k) + comb1(n - 1, k - 1);
}

/**
 * @brief pf: comb2で使われる補助関数。mからn-1までの整数の積を計算する。
 */
int pf(int m, int n) {
    long long f = 1; // オーバーフローを避けるためlong longを使用
    for (int i = m; i < n; i++) {
        f = f * i;
    }
    return (int)f;
}

/**
 * @brief comb2: 公式 nCk = n! / (k! * (n-k)!) を利用して計算
 * 長所: 高速に計算できる
 * 短所: 計算途中で階乗が巨大な数になり、オーバーフローしやすい
 */
int comb2(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    
    // nCk = nC(n-k) を利用した最適化
    if (k > n / 2) {
        k = n - k;
    }

    // 分子: n * (n-1) * ... * (n-k+1)
    // 分母: k!
    // この実装方法は問題文に準拠しているが、オーバーフローのリスクが高い
    // return pf(n - k + 1, n + 1) / pf(1, k + 1);

    // より安全な実装（乗算と除算を交互に行い、途中結果を小さく保つ）
    long long res = 1;
    for (int i = 0; i < k; ++i) {
        res = res * (n - i) / (i + 1);
    }
    return (int)res;
}

/**
 * @brief comb3: パスカルの三角形（動的計画法）を用いて計算
 * 問題文のコードはロジックに誤りがあるため、正しい実装に修正済み。
 * 長所: 高速かつ、計算途中のオーバーフローに強い。
 * 短所: わずかに余分なメモリ(配列a)を必要とする。
 */
int comb3(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }

    int a[MAXARG];
    
    // 配列を0で初期化
    for(int i = 0; i <= k; i++){
        a[i] = 0;
    }

    a[0] = 1; // iC0 = 1

    for (int i = 1; i <= n; i++) {
        // パスカルの三角形の次の行を計算
        // jを後ろから計算することで、1つの配列で更新が可能になる
        for (int j = (i < k ? i : k); j > 0; j--) {
            a[j] = a[j] + a[j-1];
        }
    }
    return a[k];
}