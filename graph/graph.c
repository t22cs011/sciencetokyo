/*
データ構造とアルゴリズムの総合演習。

ファイル: graph.c
内容: グラフの表現と、基本的な探索アルゴリズム。隣接リスト表現が応用範囲が広くおすすめ。

追加すべき関数:

Graph* create_graph(int num_vertices): グラフ構造を初期化。

void add_edge(Graph* g, int src, int dest): 辺を追加。

void bfs(Graph* g, int start_vertex): 幅優先探索（キューを使用）。

void dfs(Graph* g, int start_vertex): 深さ優先探索（再帰またはスタックを使用）。

void print_graph(Graph* g): グラフの構造を表示するヘルパー

*/