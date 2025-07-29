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

    return 0;
}