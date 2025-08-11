#include <stdio.h>
#include <stdlib.h> // mallocとexitのために必要

// ノード構造体の定義
typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

// --- 探索関数 ---
node* search(node *ptr, int key) {
    if (ptr == NULL) return(NULL);

    if (key < ptr->key) {
        return(search(ptr->left, key));
    } else if (key == ptr->key) {
        return(ptr);
    } else {
        // A: keyが現在のノードより大きい場合、右の部分木を探索
        return(search(ptr->right, key));
    }
}

// --- 挿入関数 ---
node* insert(node *root, int key) {
    node *new_node, *ptr;

    // 新しいノードのメモリ確保と初期化
    if ((new_node = malloc(sizeof(node))) == NULL) exit(1);
    new_node->key = key;
    new_node->left = new_node->right = NULL;

    // 木が空の場合、新しいノードが根(root)になる
    if (root == NULL) return(new_node);

    ptr = root;
    while (ptr != NULL) {
        if (key < ptr->key) {
            if (ptr->left == NULL) {
                ptr->left = new_node;
                break;
            }
            // B: 左の子へ移動
            ptr = ptr->left;
        } else { // key >= ptr->key の場合
            if (ptr->right == NULL) {
                ptr->right = new_node;
                break;
            }
            // C: 右の子へ移動
            ptr = ptr->right;
        }
    }
    return(root);
}

// (参考) 木の内容を通りがけ順(in-order traversal)で表示する関数
void print_inorder(node *ptr) {
    if (ptr != NULL) {
        print_inorder(ptr->left);
        printf("%d ", ptr->key);
        print_inorder(ptr->right);
    }
}

// (参考) 木のメモリを解放する関数
void free_tree(node *ptr) {
    if (ptr != NULL) {
        free_tree(ptr->left);
        free_tree(ptr->right);
        free(ptr);
    }
}


// --- main関数 ---
int main() {
    node *root = NULL; // 木の根を初期化
    int keys_to_insert[] = {11, 13, 17, 2, 3, 5, 7};
    int n = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);

    // 木に要素を挿入
    for (int i = 0; i < n; i++) {
        root = insert(root, keys_to_insert[i]);
    }

    printf("木の内容 (通りがけ順): ");
    print_inorder(root);
    printf("\n\n");

    // --- 探索のテスト ---
    int key_to_find = 7;
    node *found_node = search(root, key_to_find);
    if (found_node != NULL) {
        printf("キー %d が見つかった。\n", found_node->key);
    } else {
        printf("キー %d は見つからなかった。\n", key_to_find);
    }

    key_to_find = 99;
    found_node = search(root, key_to_find);
    if (found_node != NULL) {
        printf("キー %d が見つかった。\n", found_node->key);
    } else {
        printf("キー %d は見つからなかった。\n", key_to_find);
    }
    
    // メモリ解放
    free_tree(root);

    return 0;
}