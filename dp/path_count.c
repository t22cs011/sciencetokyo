#include <stdio.h>
// 最小値の比較に使うため、INT_MAX（int型が取りうる最大値）を定義したヘッダファイルを追加
#include <limits.h>


// 訪問した座標を記録するための構造体 (ソースコード3.4)
// 連結リストで経路を表現します。pは前のノードを指します。
struct Node {
    int x;
    int y;
    struct Node *p; //「ア」はポインタを示す *
};

int t = 0;

// ある点が既に経路に含まれているか（訪問済みか）を調べる関数 (ソースコード3.4)
// n.pから始まる連結リストを遡り、nと同じ座標がないか探します。
int is_visited(struct Node n) {
    //「イ」は型、「ウ」は初期値
    struct Node *n_curr = n.p; 
    
    //「エ」はループ条件
    while (n_curr != NULL) { 
        //「オ」でリストを遡る
        // n_curr = n_curr->p; 
        //「カ」「キ」「ク」で座標を比較
        if (n_curr->x == n.x && n_curr->y == n.y)
            return 1; // 訪問済み
        // その後で、次のノード（履歴の1つ前）へポインタを進める(問題が間違ってる？)
        n_curr = n_curr->p; 
    }
    return 0; // 未訪問
}

// (0,0)から(N,N)までの全経路数を数える再帰関数 (ソースコード3.4)
int count_path(struct Node n, int N) {
    int res = 0;
    // 移動方向の定義 (上, 下, 左, 右) 注意：デカルト座標系ではなく、左上が(0,0)で右下が(n, n)になっている
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // 現在地が既に訪問済みなら、この経路は無効 (「ケ」)
    if (is_visited(n)) {
        return 0;
    }

    // ゴール(N,N)に到達した場合 (「コ」「サ」「ス」)
    if (n.x == N && n.y == N) {
        return 1; // 1つの有効な経路としてカウント
    }

    // 4方向への移動を試す
    for (int i = 0; i < 4; i++) {
        // 次の座標を計算 (「セ」「ソ」)
        int x = n.x + dx[i];
        int y = n.y + dy[i];

        // 次のノードを準備
        struct Node n_new;
        // グリッドの範囲外ならスキップ (「タ」「チ」「ツ」「テ」)
        if (x < 0 || y < 0 || x > N ||  y > N) {
            continue;
        }

        // 問8
        t++;
        if(t < 5)
            // printf("%d %d\n", x, y);
        
        n_new.x = x;
        n_new.y = y;
        n_new.p = &n; // 現在のノードを前のノードとして設定 (「ヌ」)

        // 再帰呼び出しで、次のノードからの経路数を加算 (「ネ」「ノ」)
        res += count_path(n_new, N);
        //問9
        // t++;
        // if(t < 5)
        //     // printf("count_path %d\n", res);
        //     printf("%d %d\n", x, y);
    }

    return res;
}

// ----- 以下に最小経路和を求めるコードを追加 -----

// (0,0)から(N,N)までの最小経路和を求める再帰関数
// グリッドの各マスのコスト（重み）を渡すために、引数に cost_grid を追加した
int find_min_path_sum(struct Node n, int N, const int cost_grid[N+1][N+1]) {
    // is_visited関数で訪問済みかチェックし、ループを防ぐ
    if (is_visited(n)) {
        // 訪問済みのマスに再度到達した場合、この経路は無効とみなし、非常に大きな値を返す
        return INT_MAX;
    }

    // ベースケース (Base Case): ゴール(N,N)に到達した場合
    if (n.x == N && n.y == N) {
        // ゴール地点のコストを返す
        return cost_grid[n.x][n.y];
    }

    // この地点からゴールまでの最小経路和を格納する変数。INT_MAXで初期化する
    int min_sum = INT_MAX;
    
    // 移動方向の定義 (上, 下, 左, 右)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // 4方向への移動を試す
    for (int i = 0; i < 4; i++) {
        // 次のノードの座標を計算
        int x = n.x + dx[i];
        int y = n.y + dy[i];

        // グリッドの範囲外なら、この方向への移動はスキップする
        if (x < 0 || y < 0 || x > N || y > N) {
            continue;
        }

        // 次のノードを作成
        struct Node n_new;
        n_new.x = x;
        n_new.y = y;
        // 現在のノードを親としてポインタを繋ぎ、経路履歴を記録する
        n_new.p = &n;

        // 再帰呼び出し (Recursive Call): 次のノードからゴールまでの最小経路和を求める
        int sum = find_min_path_sum(n_new, N, cost_grid);

        // 再帰呼び出しが有効な経路（INT_MAXでない）を返した場合、最小値を更新するか検討する
        if (sum != INT_MAX) {
            // これまでに見つかった最小和（min_sum）より小さい和が見つかった場合
            if (sum < min_sum) {
                // min_sumを更新する
                min_sum = sum;
            }
        }
    }

    // 4方向の探索後、有効な経路が一つも見つからなかった場合（min_sumがINT_MAXのまま）
    if (min_sum == INT_MAX) {
        // この地点からはゴールに到達できないことを示すため、INT_MAXを返す
        return INT_MAX;
    }

    // 現在地のコストと、この先（ゴールまで）の最小経路和を足して返す
    return cost_grid[n.x][n.y] + min_sum;
}


// メイン関数 (ソースコード3.3)
int main() {
    // --- 元のコード（全経路数の計算） ---
    // スタート地点(0,0)を設定
    struct Node n;
    n.x = 0;
    n.y = 0;
    n.p = NULL; // スタートなので前のノードはない

    // 3x3グリッドでの全経路数を出力
    printf("Total paths for N=3: %d\n", count_path(n, 3));

    // --- 追加したコード（最小経路和の計算） ---
    // 各マスのコストを定義したグリッド (cost_grid)
    // 例えば、(0,0)のコストは1、(0,1)のコストは3
    const int N = 3;
    const int cost_grid[N+1][N+1] = {
        {1, 3, 5, 2},
        {8, 2, 4, 1},
        {4, 1, 9, 7},
        {2, 6, 3, 1}
    };
    
    // 最小経路和計算用のスタート地点を再度設定
    struct Node start_node_min;
    start_node_min.x = 0;
    start_node_min.y = 0;
    start_node_min.p = NULL;

    // find_min_path_sum関数を呼び出し、結果を格納
    int min_path_sum = find_min_path_sum(start_node_min, N, cost_grid);

    // 最小経路和の結果を出力
    printf("Minimum path sum for N=3: %d\n", min_path_sum);

    return 0;
}