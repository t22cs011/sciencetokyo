/*追加予定

追加すべき関数:

TNode* insert_node(TNode* root, int data): データを木に挿入する（再帰）。

TNode* search_node(TNode* root, int data): データを探索する（再帰）。

TNode* delete_node(TNode* root, int data): データを削除する（最難関）。

void inorder(TNode* root): 中間順巡回（昇順で出力される）。

void preorder(TNode* root): 先行順巡回。

void postorder(TNode* root): 後行順巡回。

void free_tree(TNode* root): 木全体のメモリを解放する。

AVL木

*/


#include <stdio.h>  // printfなどの標準入出力関数を使用
#include <stdlib.h> // malloc, exitなどの標準ライブラリ関数を使用

// 二分探索木のノード（節点）の定義
typedef struct node {
    int key;                // ノードが持つ整数値
    struct node *left;      // 左の子ノードへのポインタ
    struct node *right;     // 右の子ノードへのポインタ
} node;

// --- 関数のプロトタイプ宣言 ---
node* insert(node *root, int key);
node* search(node *ptr, int key);
void print_inorder(node *ptr);
void free_tree(node *ptr);

/**
 * @brief 指定されたキーを持つノードを探索する（画像準拠版）
 * @param ptr 現在調べているノードへのポインタ
 * @param key 探索する値
 * @return 見つかったノードへのポインタ。なければNULL。
 */
node* search(node *ptr, int key) {
    if (ptr == NULL) return(NULL);                  // 見つからなかった場合
    if (key < ptr->key) return(search(ptr->left, key)); // キーが小さければ左を探索
    else if (key == ptr->key) return(ptr);           // キーが一致すればノードを返す
    else return(search(ptr->right, key));           // キーが大きければ右を探索
}

/**
 * @brief 新しいキーを二分探索木に挿入する（画像準拠版）
 * @param root 木の根（ルート）へのポインタ
 * @param key 挿入する値
 * @return 挿入後の木の根へのポインタ
 */
node* insert(node *root, int key) {
    node *new, *ptr; // new: 新規ノード用ポインタ, ptr: 探索用ポインタ

    // 新規ノードのメモリを確保
    if ((new = malloc(sizeof(node))) == NULL) exit(1);
    
    // 新規ノードの初期化
    new->key = key;
    new->left = new->right = NULL;

    // 木が空の場合、新しいノードが根になる
    if (root == NULL) return(new); /* first node as root */
    
    ptr = root; // 探索を根から開始
    while (ptr != NULL) { // breakで抜けるまでループ
        if (key < ptr->key) { // 挿入キーが現在位置のキーより小さい場合
            if (ptr->left == NULL) { // 左の子が空なら
                ptr->left = new; // そこに新しいノードを接続
                break;           // 挿入完了なのでループを抜ける
            }
            ptr = ptr->left; // 左の子へ進む
        } else { // 挿入キーが現在位置のキー以上の場合
            if (ptr->right == NULL) { // 右の子が空なら
                ptr->right = new; // そこに新しいノードを接続
                break;            // 挿入完了なのでループを抜ける
            }
            ptr = ptr->right; // 右の子へ進む
        }
    }
    return(root); // 更新された木の根を返す
}

/**
 * @brief 木の内容を通りがけ順（In-order）で表示する
 * @param ptr 現在のノードへのポインタ
 */
void print_inorder(node *ptr) {
    if (ptr == NULL) return;
    print_inorder(ptr->left);
    printf("%d ", ptr->key);
    print_inorder(ptr->right);
}

/**
 * @brief 木が使用しているメモリをすべて解放する
 * @param ptr 現在のノードへのポインタ
 */
void free_tree(node *ptr) {
    if (ptr == NULL) return;
    free_tree(ptr->left);
    free_tree(ptr->right);
    free(ptr);
}

// --- メイン関数（動作確認用） ---
int main(void) {
    node *root = NULL; // 木の根を指すポインタ

    // 挿入するキーの配列
    int keys[] = {5, 3, 8, 2, 4, 7, 17, 16, 21, 18, 22};
    int n = sizeof(keys) / sizeof(keys[0]);
    int i;

    // キーを順番に挿入して木を構築
    printf("木を構築します...\n");
    for (i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    // 構築した木を表示
    printf("構築された木（昇順）: ");
    print_inorder(root);
    printf("\n\n");

    // 探索のテスト
    int key_to_find = 18;
    printf("キー %d を探索します...\n", key_to_find);
    if (search(root, key_to_find) != NULL) {
        printf("結果: 見つかりました。\n");
    } else {
        printf("結果: 見つかりませんでした。\n");
    }

    // メモリの解放
    free_tree(root);

    return 0;
}