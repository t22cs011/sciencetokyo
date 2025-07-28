/* 最短路問題に対するダイクストラ法のプログラム例 */

#include <stdio.h>    // 標準入出力ライブラリ (printf, fopen, fscanf などを使用)
#include <stdlib.h>   // 標準ライブラリ (malloc, exit などを使用)

#define N 100         // 扱えるノード(節点)数の上限
#define M 500         // 扱えるエッジ(枝)数の上限
#define ZERO 0.0001   // float型の数値を比較する際の、丸め誤差の許容値

/* 構造体edge: グラフのエッジ(枝)を表す*/
struct edge
{
    float d;      // d: エッジの重み(距離)
    int end1;     // end1: エッジの端点となるノード1の番号
    int end2;     // end2: エッジの端点となるノード2の番号
};

/* 構造体: value
 * 役割: ヒープ(優先度付きキュー)に格納される要素を表す。
 */
struct value
{
    float d;      // d: 始点からの暫定的な最短距離
    int node;     // node: ノードの番号
};

/* 構造体: cell
 * 役割: グラフの隣接リスト(adjacency list)を構成する要素(セル)。
 */
struct cell
{
    int adj;           // adj: 隣接しているノードの番号
    int edge;          // edge: そのノードに接続しているエッジの(E配列における)インデックス
    struct cell *next; // *next: 同じ始点を持つ次のcellへのポインタ
};


void dijkstra(struct edge *E, struct edge *T, float *d, int n, int m); // ダイクストラ法を実行するメイン関数
struct value deletemin(struct value *A, int *loc, int n); // ヒープから最小値を持つ要素を削除し、その値を返す
void downmin(int i, struct value *A, int *loc, int n); // ヒープのi番目の要素を下に沈めて、ヒープ条件を回復させる
void insert(struct value dj, struct value *A, int *loc, int n); // ヒープに新しい要素を挿入する
void upmin(int i, struct value *A, int *loc, int n); // ヒープのi番目の要素を上に浮かび上がらせて、ヒープ条件を回復させる
void swap(int i, int j, struct value *A, int *loc); // ヒープのi番目とj番目の要素を交換する


main()
{
    struct edge E[M], T[N-1]; // E: ファイルから読み込んだグラフの全エッジ情報を格納する配列, T: 計算された最短路木(Shortest Path Tree)のエッジ情報を格納する配列
    float dstar[N];           // dstar: 始点から各ノードへの最短路長を格納する配列
    int i, k, n, m;           // i, k: ループカウンタ, n: 実際のノード数, m: 実際のエッジ数
    FILE *file;               // file: 読み込むデータファイルへのポインタ

    // "spathdata"ファイルを読み込みモードで開く
    file = fopen("spathdata", "r");
    
    // 1行目からノード数nとエッジ数mを読み込む
    fscanf(file, "%d", &n);
    fscanf(file, "%d", &m);
    
    // m個のエッジ情報をファイルから読み込み、E配列に格納する
    for (i = 0; i < m; i++)
    {
        fscanf(file, "%f", &E[i].d);
        fscanf(file, "%d", &E[i].end1);
        fscanf(file, "%d", &E[i].end2);
    }
    fclose(file); // ファイルを閉じる

    printf("n = %d, m = %d\n", n, m);
    printf("edges; d  end1  end2 \n");
    for (i = 0; i < m; i++)
    {
        printf("%f, %d, %d\n", E[i].d, E[i].end1, E[i].end2);
    }
    
    dijkstra(E, T, dstar, n, m); // ダイクストラ法の実行

    printf("\nShortest path tree edges\n"); // 最短路木を構成するエッジ
    for (k = 0; k < n - 1; k++)
    {
        printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
    }
    
    printf("\nShortest path length\n"); // 始点から各ノードへの最短路長
    for (k = 0; k < n; k++)
    {
        printf("node %d: %f\n", k, dstar[k]);
    }

    return (0);
}

/* dijkstra関数
 * 役割: ダイクストラ法のアルゴリズム本体。始点0から各ノードへの最短路を計算する。
 * 引数:
 * E: グラフの全エッジ配列, T: 結果(最短路木)を格納する配列, dstar: 結果(最短路長)を格納する配列
 * n: ノード数, m: エッジ数
 */
void dijkstra(struct edge *E, struct edge *T, float *dstar, int n, int m)
{
    int i, j, k, u, v1, v2, vadj, nh;
    int P[N];           // P: 最短路が確定したノードの集合。P[i]=1なら確定済み、0なら未確定。
    int loc[N];         // loc: ノード番号からヒープ配列内のインデックスを引くためのマップ。loc[i]=-1ならヒープにない。
    int edge[N];        // edge: 最短路木において、各ノードへの流入エッジのインデックスを保存する。
    float du;           // du: 現在注目しているノードuへの最短路長。
    struct cell *adjlist[N]; // adjlist: グラフの隣接リスト表現。
    struct cell *r, *q, *p;  // r, q, p: 隣接リストを操作するためのポインタ。
    struct value vh, vmin;   // vh: ヒープに挿入するための一時的なvalue, vmin: ヒープから取り出した最小値を持つ要素。
    struct value heap[N-1];  // heap: 未確定ノードを管理する最小ヒープ(優先度付きキュー)。

    P[0] = 1;                           // 始点(ノード0)を確定済み集合Pに入れる
    for (j = 1; j < n; j++) P[j] = 0;   // 他はすべて未確定
    for (j = 0; j < n; j++)             // 隣接リストとloc配列を初期化
    {
        adjlist[j] = NULL;
        loc[j] = -1;
    }
    
    // エッジ配列Eから隣接リストを構築する
    for (i = 0; i < m; i++)
    {
        v1 = E[i].end1;
        v2 = E[i].end2;
        r = (struct cell *)malloc(sizeof(struct cell)); // v1 -> v2 の接続を追加
        r->adj = v2; r->edge = i; r->next = adjlist[v1]; adjlist[v1] = r;
        q = (struct cell *)malloc(sizeof(struct cell)); // v2 -> v1 の接続を追加 (無向グラフのため)
        q->adj = v1; q->edge = i; q->next = adjlist[v2]; adjlist[v2] = q;
    }

    nh = 0;                             // ヒープの要素数を0に初期化
    u = 0;                              // 始点ノードを0に設定
    du = 0.0; dstar[u] = 0.0;           // 始点の最短路長は0
    
    // 全てのノードが確定するまで (n-1回) 繰り返す
    for (k = 0; k < n - 1; k++)
    {
        // 現在のノードuに隣接するすべてのエッジを調べる
        p = adjlist[u];
        while (p != NULL)
        {
            vadj = p->adj;              // uに隣接するノードvadj

            if (P[vadj] == 0)           // vadjがまだ未確定の場合のみ処理
            {
                if (loc[vadj] == -1)    // vadjがまだヒープにない場合
                {
                    vh.d = du + E[p->edge].d; // 新しい距離を計算し、ヒープに挿入する
                    vh.node = vadj;
                    edge[vadj] = p->edge;
                    insert(vh, heap, loc, nh);
                    nh = nh + 1;        // ヒープサイズをインクリメント
                }
                else                    // vadjがすでにヒープにある場合
                {
                    j = loc[vadj];      // ヒープ内でのvadjの位置
                    if (heap[j].d > du + E[p->edge].d + ZERO) // uを経由した方が距離が短い場合、ヒープ内の距離を更新
                    {
                        heap[j].d = du + E[p->edge].d;
                        edge[vadj] = p->edge;
                        upmin(j, heap, loc, nh); // ヒープ条件を回復
                    }
                }
            }
            p = p->next; // 次の隣接ノードへ
        }

        vmin = deletemin(heap, loc, nh); // ヒープから最短距離が最小のノードを取り出す
        nh = nh - 1;                     // ヒープサイズをデクリメント

        u = vmin.node;     // 取り出したノードを新たなuとする
        du = vmin.d;
        P[u] = 1;          // uを確定済み集合Pに入れる
        dstar[u] = du;     // uへの最短路長を確定
        T[k] = E[edge[u]]; // uへの道を最短路木Tに追加
    }
    return;
}

/* insert関数
 * 役割: ヒープAに新しい要素vhを挿入する。
 * 引数:
 * vh: 挿入する要素, A: ヒープ配列, loc: locマップ
 * n: 挿入前のヒープの要素数
 */
void insert(struct value vh, struct value *A, int *loc, int n)
{
    A[n] = vh;            // ヒープの末尾に要素を追加
    loc[A[n].node] = n;   // locマップを更新
    upmin(n, A, loc, n + 1); // 追加した要素を適切な位置まで浮かび上がらせる
}

/* deletemin関数
 * 役割: ヒープAから最小要素(根)を削除し、その値を返す。
 * 引数:
 * A: ヒープ配列, loc: locマップ, n: 削除前のヒープの要素数
 */
struct value deletemin(struct value *A, int *loc, int n)
{
    struct value min; // 削除する最小値を格納する変数

    min = A[0];            // 根の要素(最小値)を保存
    A[0] = A[n - 1];       // 根にヒープの末尾の要素を移動
    loc[A[0].node] = 0;    // locマップを更新
    
    if (n > 1)
    {
        downmin(0, A, loc, n - 1); // 根に移動した要素を適切な位置まで沈める
    }
    return (min);
}

/* upmin関数 (sift-up)
 * 役割: A[i]から根の方向へ、ヒープ条件を回復させる。
 * 引数:
 * i: 対象要素のインデックス, A: ヒープ配列, loc: locマップ, n: ヒープの全要素数
 */
void upmin(int i, struct value *A, int *loc, int n)
{
    int j; // 親ノードのインデックス

    if (i < 0 || i >= n)
    {
        printf("Illegal element i = %d for n = %d\n", i, n);
        exit(1);
    }
    if (i == 0) return; // 根に到達したら終了

    j = (i - 1) / 2; // 親ノードのインデックスを計算

    if (A[j].d > A[i].d) // 親の方が大きい場合(最小ヒープ条件を満たさない場合)
    {
        swap(i, j, A, loc); // 親と子を交換
        upmin(j, A, loc, n); // 交換先の位置で再帰的に実行
    }
    return;
}

/* downmin関数 (sift-down)
 * 役割: A[i]から葉の方向へ、ヒープ条件を回復させる。
 * 引数:
 * i: 対象要素のインデックス, A: ヒープ配列, loc: locマップ, n: ヒープの全要素数
 */
void downmin(int i, struct value *A, int *loc, int n)
{
    int j; // 小さい方の子のインデックス

    if (i < 0 || i >= n)
    {
        printf("Illegal element i = %d for n = %d\n", i, n);
        exit(1);
    }
    
    j = 2 * i + 1; // 左の子のインデックスを計算
    if (j >= n) return; // 子が存在しない場合(葉の場合)は終了

    if (j + 1 < n && A[j].d > A[j + 1].d + ZERO) // 右の子が存在し、かつ右の子の方が小さい場合、jを右の子のインデックスにする
    {
        j = j + 1;
    }

    if (A[j].d < A[i].d - ZERO) // 子の方が小さい場合(最小ヒープ条件を満たさない場合)
    {
        swap(i, j, A, loc);   // 親と子を交換
        downmin(j, A, loc, n); // 交換先の位置で再帰的に実行
    }
    return;
}

/* swap関数
 * 役割: ヒープA内の2つの要素A[i]とA[j]を交換する。
 * 引数:
 * i, j: 交換する要素のインデックス, A: ヒープ配列, loc: locマップ
 */
void swap(int i, int j, struct value *A, int *loc)
{
    struct value temp;

    temp = A[i]; // A[i]とA[j]の値を交換
    A[i] = A[j];
    A[j] = temp;

    loc[A[i].node] = i; // locマップ(ノード番号->ヒープ内インデックス)も更新する
    loc[A[j].node] = j;
    
    return;
}