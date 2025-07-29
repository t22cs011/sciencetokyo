#include <stdio.h>

// ソースコード 3.2 で使用するグローバル配列
// W=17, H=13 を十分にカバーするサイズを確保
int a[25][25];

// --- 関数プロトタイプ宣言 ---
int count_shortest_path_recursive(int w, int h);
int count_shortest_path_dp(int w, int h);
int count_shortest_path_recursive_blocked(int w, int h);


/**
 * @brief ソースコード 3.1 (再帰)
 * (0,0)から(w,h)への最短経路数を計算する。
 */
int count_shortest_path_recursive(int w, int h) {
    // ベースケース: w=0またはh=0のとき、経路は1通り
    if (w == 0 || h == 0) {
        return 1; // 空欄 A
    }
    // 再帰ステップ
    return count_shortest_path_recursive(w - 1, h) + count_shortest_path_recursive(w, h - 1); // 空欄 B, C
}


/**
 * @brief ソースコード 3.2 (動的計画法)
 * (0,0)から(w,h)への最短経路数を計算する。
 */
int count_shortest_path_dp(int w, int h) {
    // y軸の初期化 (a[i][0] = 1)
    for (int i = 0; i <= h; i++) {
        a[i][0] = 1; // 空欄 あ
    }
    // x軸の初期化 (a[0][i] = 1)
    for (int i = 0; i <= w; i++) {
        a[0][i] = 1; // 空欄 い
    }
    
    // DPテーブルの残りを埋める
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            // (i,j)への経路は、下(i-1,j)からと左(i,j-1)からの和
            a[i][j] = a[i - 1][j] + a[i][j - 1]; // 空欄 う,え,お,き
        }
    }
    
    return a[h][w]; // 空欄 か,き
}

/**
 * @brief 問6の仕様 (通行止めありの再帰)
 * (8,7)を通行止めとして最短経路数を計算する。
 */
int count_shortest_path_recursive_blocked(int w, int h) {
    // 通行止め地点(8,7)に到達した場合は0を返す
    if (w == 8 && h == 7) {
        return 0;
    }
    // ベースケース
    if (w == 0 || h == 0) {
        return 1;
    }
    // 再帰ステップ
    return count_shortest_path_recursive_blocked(w - 1, h) + count_shortest_path_recursive_blocked(w, h - 1);
}


int main() {
    printf("--- C-Code Implementation for Grid Path Problem ---\n\n");

    // 問1: W=6, H=5 のときの最短経路数
    printf("## 問1 (W=6, H=5)\n");
    printf("Result by DP: %d\n", count_shortest_path_dp(6, 5));
    // 再帰は非常に遅くなるためコメントアウト
    // printf("Result by Recursion: %d\n", count_shortest_path_recursive(6, 5));
    printf("----------------------------------------\n\n");

    // 問5 & 6: W=17, H=13 で (8,7)が通行止めの場合
    printf("## 問5 & 問6 (W=17, H=13, block at (8,7))\n");
    
    // 問5の解法: (全体) - (通行止め経由)
    int total_paths = count_shortest_path_dp(17, 13);
    int paths_to_block = count_shortest_path_dp(8, 7);
    int paths_from_block = count_shortest_path_dp(17 - 8, 13 - 7);
    int result_by_subtraction = total_paths - (paths_to_block * paths_from_block);
    
    printf("[問5] 手計算方式での結果: %d\n", result_by_subtraction);
    printf(" (Total: %d, ToBlock: %d, FromBlock: %d)\n\n", total_paths, paths_to_block, paths_from_block);

    // 問6の解法: 通行止めを組み込んだ再帰関数
    // 注意: W,Hが大きいと計算に時間がかかる
    int result_by_blocked_recursion = count_shortest_path_recursive_blocked(17, 13);
    printf("[問6] 通行止めを考慮した再帰関数の結果: %d\n", result_by_blocked_recursion);
    printf("----------------------------------------\n");

    return 0;
}