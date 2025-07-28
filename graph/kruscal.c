/* 最小木問題に対するクラスカル法のプログラム例 */

#include <stdio.h>
#include <math.h>

#define N 100        /* 節点数(頂点数)の上限 */
#define M 500        /* 枝数(辺の数)の上限 */
#define ZERO 0.0001  /* 丸め誤差の許容値 */

/* 辺の情報を格納する構造体 */
struct edge
{
    float d;            /* d: 辺の重み（枝長） */
    int end1, end2;     /* end1, end2: 辺の両端の頂点 */
};

/* Union-Find木を管理するための構造体 */
struct set
{
    int size[N];    /* size: 各集合の要素数 */
    int root[N];    /* root: 各集合の根のインデックス */
    int parent[N];  /* parent: 各頂点の親のインデックス */
};

/* 関数のプロトタイプ宣言 */
void kruskal(struct edge *E, struct edge *T, int n, int m);
void quicksort(int i, int j, struct edge *A);
int partition(int i, int j, float a, struct edge *A);
int pivot(int i, int j, struct edge *A);
void swap(int i, int j, struct edge *A);
void treemerge(int i, int k, struct set *S);
int treefind(int j, struct set *S);

/* メイン関数: プログラムの実行開始点 */
main()
{
    /* 変数の宣言 */
    struct edge E[M];           /* E: ファイルから読み込むグラフの全辺を格納する配列 */
    struct edge T[N - 1];       /* T: 構築する最小全域木(MST)の辺を格納する配列 */
    int i, k;                   /* i, k: ループカウンタ */
    int n, m;                   /* n: 頂点数, m: 辺数 */
    FILE *file;                 /* file: データファイルへのポインタ */

    /* ファイルを開く */
    file = fopen("edgedata", "r");

    /* ファイルから頂点数と辺数を読み込む */
    fscanf(file, "%d", &n);
    fscanf(file, "%d", &m);

    /* ファイルから各辺の情報を読み込む */
    for (i = 0; i < m; i++)
    {
        fscanf(file, "%f", &E[i].d);      // 辺の重みを読み込む
        fscanf(file, "%d", &E[i].end1);   // 端点1を読み込む
        fscanf(file, "%d", &E[i].end2);   // 端点2を読み込む
    }

    /* 読み込んだグラフ情報を画面に表示 */
    printf("n = %d, m = %d\n", n, m);
    printf("edges; d  end1  end2 \n");
    for (i = 0; i < m; i++)
    {
        printf("%f, %d, %d\n", E[i].d, E[i].end1, E[i].end2);
    }

    /* クラスカル法を実行して最小全域木を求める */
    kruskal(E, T, n, m);

    /* 結果（最小全域木を構成する辺）を画面に表示 */
    printf("MST edges\n");
    for (k = 0; k < n - 1; k++)
    {
        printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
    }

    return (0); // プログラムの正常終了
}


/**
 * @brief クラスカル法を用いて最小全域木を求める関数
 * @param E グラフの全辺の配列
 * @param T 最小全域木の結果を格納する配列
 * @param n 頂点数
 * @param m 辺数
 */

 /* MSTを構築する関数
 1. Union-Find木の初期化: 全ての頂点をそれぞれ独立した集合とする
 2. 全ての辺を重みが小さい順にquickソート
 3. 辺を順番に見ていき、MSTを構築する
 
 */
void kruskal(struct edge *E, struct edge *T, int n, int m)
{
    /* 変数の宣言 */
    struct set comp;    /* comp: 頂点集合を管理するUnion-Find木 */
    int i, j, k;        /* i, j, k: ループカウンタ (i:全辺, j:初期化, k:MSTの辺) */
    int s1, s2;         /* s1, s2: 辺の両端点が属する集合の根 */

    /* Union-Find木の初期化: 全ての頂点をそれぞれ独立した集合とする */
    for (j = 0; j < n; j++)
    {
        comp.size[j] = 1;         // 各集合のサイズを1に
        comp.root[j] = j;         // 各集合の根を自分自身に
        comp.parent[j] = -j - 1;  // 親を負の値にして根であることを示す
    }

    /* ステップ1: 全ての辺を重みが小さい順にソートする */
    quicksort(0, m - 1, E);

    /* ステップ2: 辺を順番に見ていき、MSTを構築する */
    k = 0; // MSTに追加した辺のカウンタを初期化
    i = 0; // ソート済み辺配列のインデックスを初期化
    while (k < n - 1) // MSTの辺の数が (頂点数 - 1) になるまで繰り返す
    {
        /* 辺の両端点が属する集合の根を調べる */
        s1 = treefind(E[i].end1, &comp);
        s2 = treefind(E[i].end2, &comp);

        /* 根が異なる場合（＝閉路ができない場合）のみ辺をMSTに追加 */
        if (s1 != s2)
        {
            treemerge(s1, s2, &comp); // 2つの集合を統合
            T[k] = E[i];              // この辺をMSTに追加
            k = k + 1;                // MSTの辺カウンタを増やす
        }
        i = i + 1; // 次の辺へ（追加したかどうかに関わらず）
    }

    return;
}

/**
 * @brief 配列A[i]からA[j]までをクイックソートで整列させる
 */
void quicksort(int i, int j, struct edge *A)
{
    int pv, k; // pv: 軸要素のインデックス, k: 分割位置
    float a;   // a: 軸要素の値

    pv = pivot(i, j, A); // 軸要素を選択
    if (pv != -1)
    {
        a = A[pv].d;                   // 軸要素の値を取得
        k = partition(i, j, a, A);     // 軸要素を基準に配列を分割
        quicksort(i, k - 1, A);        // 左側の部分配列を再帰的にソート
        quicksort(k, j, A);            // 右側の部分配列を再帰的にソート
    }
    return;
}

/**
 * @brief 配列A[i]からA[j]を軸aで分割し、分割点を返す
 */
int partition(int i, int j, float a, struct edge *A)
{
    int l, r, k; // l: 左からの探索インデックス, r: 右からの探索インデックス, k: 分割点
    l = i;
    r = j;

    while (A[l].d < a - ZERO) l = l + 1;
    while (A[r].d + ZERO >= a) r = r - 1;
    while (l <= r)
    {
        swap(l, r, A);
        l = l + 1;
        r = r - 1;
        while (A[l].d < a - ZERO) l = l + 1;
        while (A[r].d + ZERO >= a) r = r - 1;
    }
    k = l;
    return (k);
}

/**
 * @brief 配列A[i]からA[j]の中から軸要素(pivot)を選び、そのインデックスを返す
 */
int pivot(int i, int j, struct edge *A)
{
    int pv, k; // pv: 軸要素のインデックス, k: 探索用インデックス

    k = i + 1;
    // A[i]と異なる値が見つかるまで探索
    while (fabs(A[i].d - A[k].d) <= ZERO && k <= j)
    {
        k = k + 1;
    }

    if (k > j) // 全ての要素が同じ場合
    {
        pv = -1;
    }
    else if (A[i].d >= A[k].d) // A[i]の方が大きい場合
    {
        pv = i;
    }
    else // A[k]の方が大きい場合
    {
        pv = k;
    }
    return (pv);
}

/**
 * @brief 構造体配列の要素A[i]とA[j]を交換する
 */
void swap(int i, int j, struct edge *A)
{
    struct edge temp; // 一時的なデータ退避用

    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    return;
}

/**
 * @brief Union-Find木において、集合iと集合kを併合する（Union by Size）
 */
void treemerge(int i, int k, struct set *S)
{
    int j, large, small; // large:大きい集合の根, small:小さい集合の根

    // サイズの小さい木を大きい木に併合する
    if (S->size[i] <= S->size[k])
    {
        small = i;
        large = k;
    }
    else
    {
        small = k;
        large = i;
    }

    j = S->root[small]; // 小さい木の根のインデックスを取得
    if (S->size[small] == 0) return; // 既に併合済みなら何もしない

    S->parent[j] = S->root[large];                   // 小さい木の根の親を大きい木の根に設定
    S->size[large] = S->size[large] + S->size[small]; // 大きい木のサイズを更新
    S->size[small] = 0;                              // 小さい木のサイズを0に
    S->root[small] = -1;                             // 併合された木の根情報を無効化
    return;
}

/**
 * @brief Union-Find木において、頂点jが属する集合の根を探し、経路圧縮を行う
 */
int treefind(int j, struct set *S)
{
    int i, k, temp; // i: 最終的な根, k: 探索用インデックス, temp: 一時保存

    k = j;
    // 親を辿って根を探す
    while (k >= 0)
    {
        k = S->parent[k];
    }
    i = -k - 1; // 根のインデックスを復元

    k = j;
    // 根までの経路上のノードを全て根に直接つなぎ替える（経路圧縮）
    while (k >= 0)
    {
        temp = S->parent[k];
        if (temp >= 0)
        {
            S->parent[k] = S->root[i];
        }
        k = temp;
    }
    return (i); // 根のインデックスを返す
}