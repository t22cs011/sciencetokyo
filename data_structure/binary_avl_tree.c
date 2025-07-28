#include <stdio.h>
#include <stdlib.h>

// 構造体定義 (プログラム 3.1)
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// --- 関数プロトタイプ宣言 ---
int height(struct node* p);
struct node* create(int data);
struct node* insert(struct node* p, int data); // BST挿入関数を追加
struct node* rotate_left(struct node* p);
struct node* rotate_right(struct node* p);
struct node* insert_avl(struct node* p, int data);


// 木の高さを計算する関数 (プログラム 3.3 の実装に統一)
int height(struct node* p) {
    if (p == NULL) return -1;
    int left = 1 + height(p->left);
    int right = 1 + height(p->right);
    if (left > right) return left;
    else return right;
}

// 新しいノードを生成する関数 (プログラム 3.4)
struct node* create(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data; // 空欄 イ, ウ
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;       // 空欄 エ
}

// 二分探索木にノードを挿入する関数 (プログラム 3.5)
struct node* insert(struct node* p, int data) {
    if (p == NULL) { // 空欄 オ
        p = create(data);
    } else if (data > p->data) {
        p->right = insert(p->right, data); // 空欄 カ
    } else {
        p->left = insert(p->left, data);   // 空欄 キ
    }
    return p;
}

// 左回転を行う関数 (プログラム 3.8)
struct node* rotate_left(struct node* p) {
    struct node* right_child = p->right;   // 空欄 ソ
    p->right = right_child->left;          // 空欄 タ, チ
    right_child->left = p;                 // 空欄 ツ
    return right_child;
}

// 右回転を行う関数 (rotate_leftの逆操作)
struct node* rotate_right(struct node* p) {
    struct node* left_child = p->left;
    p->left = left_child->right;
    left_child->right = p;
    return left_child;
}

// AVL木にノードを挿入する関数 (プログラム 3.7)
struct node* insert_avl(struct node* p, int data) {
    // 1. 通常の二分探索木と同様に挿入
    if (p == NULL) {
        return create(data);
    }
    if (data > p->data) {
        p->right = insert_avl(p->right, data);
    } else if (data < p->data) { // 重複を許さない場合
        p->left = insert_avl(p->left, data);
    } else {
        return p; // 重複データは挿入しない
    }

    // 2. 平衡係数(balance factor)をチェックして回転処理
    int balance = height(p->left) - height(p->right);

    // 左部分木が重い場合 (LL or LR)
    if (balance > 1 && data < p->left->data) { // LL
        return rotate_right(p);
    }
    if (balance > 1 && data > p->left->data) { // LR (空欄 ス, セ)
        p->left = rotate_left(p->left);
        return rotate_right(p);
    }

    // 右部分木が重い場合 (RR or RL)
    if (balance < -1 && data > p->right->data) { // RR (空欄 ケ)
        return rotate_left(p);
    }
    if (balance < -1 && data < p->right->data) { // RL (空欄 コ, サ)
        p->right = rotate_right(p->right);
        return rotate_left(p);
    }

    return p;
}


// メイン関数 (プログラム 3.6)
int main(void) {
    // 挿入するデータ配列 (空欄 ク)
    int data[7] = {0, 2, 3, 4, 6, 1, 5};
    struct node* root = NULL;
    struct node* root_avl = NULL;

    for (int i = 0; i < 7; i++) {
        root = insert(root, data[i]);
    }
    printf("height: %d\n", height(root));

    for (int i = 0; i < 7; i++) {
        root_avl = insert_avl(root_avl, data[i]);
    }

    printf("AVL tree height: %d\n", height(root_avl));

    return 0;
}
