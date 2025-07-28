#include <stdio.h>
#include <stdlib.h>

// =================================================================
// 共通の構造体定義 (Common Struct Definition)
// =================================================================
typedef struct CELL {
    int data;
    struct CELL *next;
} CELL;


// =================================================================
// 共通のヘルパー関数 (Common Helper Functions)
// =================================================================

// 問(2)a) で与えられたメモリ確保関数
CELL *CELL_alloc(int data) {
    CELL *p = (CELL *)malloc(sizeof(CELL));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }
    p->data = data;
    p->next = NULL;
    return p;
}

// リストの内容を表示する関数
void print_list(const char* name, CELL *head) {
    printf("%s: ", name);
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    CELL *p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// リストのメモリを解放する関数
void free_list(CELL *head) {
    CELL *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}


// =================================================================
// 問(2)a) 線形リスト・挿入 (ソート済み)
// =================================================================
CELL *insert1(CELL *head, int data) {
    CELL *new = CELL_alloc(data); // 問題文の `new` に相当
    CELL *p = head;

    // 先頭に挿入する条件
    // 空欄A: p == NULL (リストが空)
    // 空欄B: data < p->data (新しいデータが先頭より小さい)
    if (p == NULL || data < p->data) {
        new->next = p; // 先頭に挿入
        return new;    // 新しい先頭を返す
    } else {
        // 挿入箇所を探す
        // 空欄C: p->next != NULL (リストの末尾まで)
        // 空欄D: p->next->data < data (挿入箇所を見つけるまで)
        while (p->next != NULL && p->next->data < data) {
            p = p->next;
        }
        // pの次に挿入
        new->next = p->next;
        p->next = new;
        return head; // 先頭は変わらない
    }
}


// =================================================================
// 問(2)b) ポインタのポインタを使う挿入
// =================================================================
void insert2(CELL **head_p, int data) {
    CELL *new = CELL_alloc(data);
    CELL **p = head_p;

    // 空欄E: *p != NULL (注目しているポインタがNULLでない)
    // 空欄F: (*p)->data < data (注目しているノードのデータが小さい)
    while (*p != NULL && (*p)->data < data) {
        // 空欄G: &((*p)->next) (次のnextメンバのアドレスを指す)
        p = &((*p)->next);
    }
    new->next = *p;
    *p = new;
}


// =================================================================
// 問(3)a) 素朴な再帰で逆順にする
// =================================================================
CELL *reverse1(CELL *head) {
    CELL *p = NULL;
    // 再帰の基底条件: リストが空か、要素が1つ
    if (head == NULL || head->next == NULL) {
        return head;
    }
    // 再帰呼び出し: headの次の要素からなるリストを逆順にする
    p = reverse1(head->next);
    // ポインタの繋ぎ変え: headをリストの末尾に移動させる
    head->next->next = head;
    head->next = NULL;
    // 新しい先頭ポインタ(元のリストの末尾)を返す
    return p;
}


// =================================================================
// 問(3)b) 途中状態を引数で渡す再帰で逆順にする
// =================================================================
CELL *reverse2(CELL *head1, CELL *head2) {
    // 再帰の基底条件: 未処理リスト(head1)が空になったら、処理済みリスト(head2)を返す
    if (head1 == NULL) {
        return head2;
    }
    // 空欄H: head1->next (次の未処理リストの先頭)
    CELL *new_head1 = head1->next;
    // 空欄I: head1->next = head2 (head1の先頭を、head2の先頭に連結)
    head1->next = head2;
    // 空欄J: head1 (新しい処理済みリストの先頭)
    CELL *new_head2 = head1;
    // 再帰呼び出し
    return reverse2(new_head1, new_head2);
}


// =================================================================
// 問(3)c) ループで逆順にする
// =================================================================
CELL *reverse3(CELL *head) {
    CELL *p1 = NULL;    // 前のノード (previous)
    CELL *p2 = head;    // 現在のノード (current)
    CELL *p3 = NULL;    // 次のノード (next)

    while (p2 != NULL) {
        // 空欄K: 次のノードを一時的に保存
        p3 = p2->next;
        // p2->next = p1 (ポインタを逆転させる)
        p2->next = p1;
        // ポインタを1つずつ右にずらす
        // 空欄L: p1 = p2
        p1 = p2;
        // 空欄M: p2 = p3
        p2 = p3;
    }
    // 新しい先頭はp1になる
    return p1;
}


// =================================================================
// main関数: 各関数の動作をシミュレーションする
// =================================================================
int main() {
    printf("H30年度 大問3 シミュレーション\n");
    printf("========================================================\n\n");

    // --- 問(2)a) insert1 のテスト ---
    printf("--- 問(2)a) insert1 (ソート済み挿入) ---\n");
    CELL *head_q2a = NULL;
    print_list("初期状態", head_q2a);
    head_q2a = insert1(head_q2a, 10);
    print_list("10を挿入", head_q2a);
    head_q2a = insert1(head_q2a, 30);
    print_list("30を挿入", head_q2a);
    head_q2a = insert1(head_q2a, 20);
    print_list("20を挿入", head_q2a);
    free_list(head_q2a);
    printf("\n");

    // --- 問(2)b) insert2 のテスト ---
    printf("--- 問(2)b) insert2 (ポインタのポインタ) ---\n");
    CELL *head_q2b = NULL;
    print_list("初期状態", head_q2b);
    insert2(&head_q2b, 10);
    print_list("10を挿入", head_q2b);
    insert2(&head_q2b, 30);
    print_list("30を挿入", head_q2b);
    insert2(&head_q2b, 20);
    print_list("20を挿入", head_q2b);
    free_list(head_q2b);
    printf("\n");

    // --- 問(3)a) reverse1 のテスト ---
    printf("--- 問(3)a) reverse1 (素朴な再帰) ---\n");
    CELL *head_q3a = CELL_alloc(10);
    head_q3a->next = CELL_alloc(20);
    head_q3a->next->next = CELL_alloc(30);
    print_list("初期状態", head_q3a);
    head_q3a = reverse1(head_q3a);
    print_list("反転後", head_q3a);
    free_list(head_q3a);
    printf("\n");

    // --- 問(3)b) reverse2 のテスト ---
    printf("--- 問(3)b) reverse2 (末尾再帰) ---\n");
    CELL *head_q3b = CELL_alloc(10);
    head_q3b->next = CELL_alloc(20);
    head_q3b->next->next = CELL_alloc(30);
    print_list("初期状態", head_q3b);
    head_q3b = reverse2(head_q3b, NULL);
    print_list("反転後", head_q3b);
    free_list(head_q3b);
    printf("\n");

    // --- 問(3)c) reverse3 のテスト ---
    printf("--- 問(3)c) reverse3 (ループ) ---\n");
    CELL *head_q3c = CELL_alloc(10);
    head_q3c->next = CELL_alloc(20);
    head_q3c->next->next = CELL_alloc(30);
    print_list("初期状態", head_q3c);
    head_q3c = reverse3(head_q3c);
    print_list("反転後", head_q3c);
    free_list(head_q3c);
    printf("\n");

    return 0;
}
