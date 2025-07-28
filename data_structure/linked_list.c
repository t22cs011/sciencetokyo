#include <stdio.h>
#include <stdlib.h>

/*typedefで構造体をCELL型として定義する*/
typedef struct CELL {
    int data;
    struct CELL *next;
} CELL;

// プロトタイプ宣言
// セル（ノード）を動的に確保し、データを設定して返す
CELL *CELL_alloc(int data);
// リストの内容を表示する
void print_list(const char *label, CELL *head);
// 昇順を保つようにリストにセルを挿入する（素朴な実装）
CELL *insert1(CELL *head, int data);
// ポインタのポインタを用いて昇順リストにセルを挿入する
void insert2(CELL **head_p, int data);
// 再帰を用いてリストを逆順にする（素朴な実装）
CELL *reverse1(CELL *head);
// 途中状態を引数で渡す、末尾再帰による逆順
CELL *reverse2(CELL *head1, CELL *head2);
// ループで逆順にする
CELL *reverse3(CELL *head);
// 指定された値を持つ最初のセルをリストから削除する
void delete(CELL **head_p, int data);
// ソート済みの2つのリストをマージする
CELL *merge_sorted_lists(CELL *headA, CELL *headB);
// リストにサイクル（循環）があるか判定する
int has_cycle(CELL *head);
// リストの中間ノードを見つける
CELL *find_middle(CELL *head);
// リストの末尾からN番目のノードを削除する
void delete_nth_from_end(CELL **head_p, int n);


/* 新しいセルを動的に確保し、データを設定してそのポインタを返すヘルパー関数 */
CELL *CELL_alloc(int data) {
    CELL *p = (CELL *)malloc(sizeof(CELL));
    if (p == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    p->data = data;
    p->next = NULL;
    return p;
}

/*リストの内容を先頭から順に表示するヘルパー関数*/
void print_list(const char *label, CELL *head) {
    printf("%s: ", label);
    CELL *p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}


/*insert1: 昇順を保つようにリストにセルを挿入する（素朴な実装）*/
CELL *insert1(CELL *head, int data) {
    CELL *new = CELL_alloc(data);
    CELL *p = head;

    // 先頭に挿入する条件
    if (p == NULL || data < p->data) { //リストが空、または先頭より小さい値なので先頭に挿入 A: p == NULL, B: data < p->data (選択肢1, 7)
        new->next = p; // newの次を現在の先頭に設定
        return new;    // newを新しい先頭として返す
    } else {
        // 挿入すべき場所を探す (pの次に挿入するため、p->nextが存在し、かつ次のデータの方が大きいかを見て判断)
        while (p->next != NULL && p->next->data < data) {        // C: p->next != NULL, D: p->next->data < data (選択肢4, 10)
            p = p->next; //次を見に行く
        }
        new->next = p->next;
        p->next = new;
        return head; // 先頭は変わらないのでheadをそのまま返す
    }
}

/*insert2: ポインタのポインタを用いて昇順リストにセルを挿入する*/
//引数は　リストの先頭を指すポインタ（main関数内のhead変数）のメモリアドレス, 追加するデータの値
void insert2(CELL **head_p, int data) {
    CELL *new = CELL_alloc(data);
    CELL **p = head_p;


    // 挿入部まで進む（pが指すポインタ(*p)がNULLでなく、その先のデータがdataより小さい間ループ　insert1と対応させると考えやすい）
    while ((*p) != NULL && (*p)->data < data) {     // E: (*p) != NULL, F: (*p)->data < data (選択肢6, 12)
        p = &((*p)->next);        // ポインタのポインタpを、次のセルのnextメンバのアドレスへ進める(選択肢17)
    }
    new->next = *p; //ポインタを繋ぎかえる
    *p = new;
}

/*reverse1: 再帰を用いてリストを逆順にする（素朴な実装）*/
CELL *reverse1(CELL *head) {
    CELL *p = NULL;
    // ベースケース: リストが空か、要素が1つしかない場合はそのまま返す
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 再帰呼び出し: headの次以降のリストを逆順にする
    p = reverse1(head->next);

    // 現在のheadを、逆順になったリストの末尾に接続する
    head->next->next = head;
    head->next = NULL; // 元の先頭を新しい末尾にする

    return p; // 新しいリストの先頭を返す
}


/*reverse2: 途中状態を引数で渡す、末尾再帰による逆順*/
/*head1は処理すべき元のリストの残り部分, head2はすでに逆順になっているリスト（計算の途中結果を保持）*/
/*呼び出し時はreverse2(head, NULL)*/
CELL *reverse2(CELL *head1, CELL *head2) {
    // ベースケース: 元のリスト(head1)が空になったら、逆順リスト(head2)を返す
    if (head1 == NULL) {
        return head2;
    }

    // H: head1->next (選択肢13)
    CELL *new_head1 = head1->next;
    // I: head1->next = head2; (head1をhead2の先頭に繋ぐ)
    head1->next = head2;
    // J: head1 (新しい逆順リストの先頭はhead1になる)
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

/*
 * delete: 指定された値を持つ最初のセルをリストから削除する
 * (insert2と同様にポインタのポインタを使用)
 */
void delete(CELL **head_p, int data) {
  CELL **p = head_p;
  CELL *target;

  // 削除対象のセル（の値がdataと一致するセル）を探す
  while ((*p) != NULL && (*p)->data != data) {
      p = &((*p)->next);
  }
  // この段階で(*p)->data == data、すなわち削除対象が見つかる
  // セルが見つかった場合
  if ((*p) != NULL) { //(*p) != NULLが成り立たなかったら、削除対象が無かったことを意味する
      target = *p;      // 削除対象のセルを一時的に保持
      *p = target->next; // ポインタを繋ぎ変えてリストから切り離す
      free(target);     // メモリを解放する
  }
}

/*
 * merge_sorted_lists: ソート済みの2つのリストをマージする
 * @param headA: 1つ目のソート済みリストの先頭ポインタ
 * @param headB: 2つ目のソート済みリストの先頭ポインタ
 * @return: マージされた新しいリストの先頭ポインタ
 */
CELL *merge_sorted_lists(CELL *headA, CELL *headB) {
    CELL dummy_node; // ダミーノード（先頭ノードの処理を簡単にするため）
    CELL *tail = &dummy_node;
    dummy_node.next = NULL;

    // 両方のリストが空になるまでループ
    while (headA != NULL && headB != NULL) {
        if (headA->data <= headB->data) {
            tail->next = headA;
            headA = headA->next;
        } else {
            tail->next = headB;
            headB = headB->next;
        }
        tail = tail->next;
    }

    // 片方のリストに残っているノードを繋げる
    tail->next = (headA != NULL) ? headA : headB;

    return dummy_node.next; // ダミーノードの次が新しい先頭
}

/*
 * has_cycle: リストにサイクルがあるかを判定する (フロイドの循環検出法)
 * @param head: リストの先頭ポインタ
 * @return: サイクルがあれば1, なければ0
 */
int has_cycle(CELL *head) {
    CELL *slow = head;
    CELL *fast = head;

    // fastがリストの終端に達するまでループ
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // 1ステップ進む
        fast = fast->next->next;    // 2ステップ進む

        // 2つのポインタが一致すればサイクルあり
        if (slow == fast) {
            return 1;
        }
    }
    return 0; // サイクルなし
}

/*
 * find_middle: リストの中間ノードを見つける
 * @param head: リストの先頭ポインタ
 * @return: 中間ノードへのポインタ (要素数が偶数の場合は後半の先頭)
 */
CELL *find_middle(CELL *head) {
    CELL *slow = head;
    CELL *fast = head;

    if (head == NULL) {
        return NULL;
    }
    
    // fastがリストの終端に達するまでループ
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

/*
 * delete_nth_from_end: リストの末尾からN番目のノードを削除する
 * @param head_p: リストの先頭を指すポインタのアドレス
 * @param n: 末尾から数えた位置 (1-indexed)
 */
void delete_nth_from_end(CELL **head_p, int n) {
    CELL *fast = *head_p;

    // fastポインタをn個先へ進める
    for (int i = 0; i < n; i++) {
        // nがリストの要素数より大きい場合、何もしない
        if (fast == NULL) {
            return;
        }
        fast = fast->next;
    }

    // fastがNULLになるまで、fastと削除対象の一つ前を指すポインタ(p)を同時に進める
    CELL **p = head_p;
    while (fast != NULL) {
        fast = fast->next;
        p = &((*p)->next);
    }
    
    // pが指すノードを削除
    CELL *target = *p;
    *p = target->next;
    free(target);
}



int main(void) {
    // --- insert1とdeleteのテスト ---
    printf("--- Test for insert1 and delete ---\n");
    CELL *head1 = NULL;
    head1 = insert1(head1, 10);
    head1 = insert1(head1, 30);
    head1 = insert1(head1, 20);
    head1 = insert1(head1, 5);
    print_list("Initial list (insert1)", head1); // 5 -> 10 -> 20 -> 30 -> NULL

    delete(&head1, 20);
    print_list("After deleting 20", head1); // 5 -> 10 -> 30 -> NULL
    delete(&head1, 5);
    print_list("After deleting 5 (head)", head1); // 10 -> 30 -> NULL
    printf("\n");

    // --- insert2とreverse1のテスト ---
    printf("--- Test for insert2 and reverse1 ---\n");
    CELL *head2 = NULL;
    insert2(&head2, 10);
    insert2(&head2, 30);
    insert2(&head2, 20);
    print_list("Initial list (insert2)", head2); // 10 -> 20 -> 30 -> NULL

    head2 = reverse1(head2);
    print_list("After reverse1", head2); // 30 -> 20 -> 10 -> NULL
    printf("\n");

    // --- reverse2のテスト ---
    printf("--- Test for reverse2 ---\n");
    CELL *head3 = NULL;
    insert2(&head3, 100);
    insert2(&head3, 200);
    insert2(&head3, 300);
    print_list("Initial list", head3); // 100 -> 200 -> 300 -> NULL
    
    // reverse2を呼び出す際は、第2引数にNULLを渡す
    head3 = reverse2(head3, NULL);
    print_list("After reverse2", head3); // 300 -> 200 -> 100 -> NULL
    
// =================================================================
    // 追加アルゴリズムのテスト
    // =================================================================
    printf("\n--- Test for added algorithms ---\n");

    // --- merge_sorted_listsのテスト ---
    CELL *listA = NULL;
    insert2(&listA, 40); insert2(&listA, 20); insert2(&listA, 10);
    CELL *listB = NULL;
    insert2(&listB, 35); insert2(&listB, 25); insert2(&listB, 15);
    print_list("List A", listA);
    print_list("List B", listB);
    CELL *merged_list = merge_sorted_lists(listA, listB);
    print_list("Merged List", merged_list);

    // --- find_middleのテスト ---
    printf("\n--- Test for find_middle ---\n");
    CELL* middle = find_middle(merged_list);
    if(middle) printf("Middle node of merged list: %d\n", middle->data);
    
    CELL *list_even = NULL;
    insert2(&list_even, 4); insert2(&list_even, 3); insert2(&list_even, 2); insert2(&list_even, 1);
    print_list("Even length list", list_even);
    middle = find_middle(list_even);
    if(middle) printf("Middle node of even list: %d\n", middle->data);


    // --- has_cycleのテスト ---
    printf("\n--- Test for has_cycle ---\n");
    CELL *cyclic_list = NULL;
    insert2(&cyclic_list, 400); insert2(&cyclic_list, 300); insert2(&cyclic_list, 200); insert2(&cyclic_list, 100);
    print_list("List for cycle test", cyclic_list);
    printf("Has cycle? %s\n", has_cycle(cyclic_list) ? "Yes" : "No");
    // サイクルを作成: 400 -> 200
    cyclic_list->next->next->next->next = cyclic_list->next; 
    printf("Creating a cycle (400 -> 200)...\n");
    printf("Has cycle? %s\n", has_cycle(cyclic_list) ? "Yes" : "No");

    // --- delete_nth_from_endのテスト ---
    printf("\n--- Test for delete_nth_from_end ---\n");
    CELL *list_del = NULL;
    insert2(&list_del, 5); insert2(&list_del, 4); insert2(&list_del, 3); insert2(&list_del, 2); insert2(&list_del, 1);
    print_list("Original list", list_del);
    
    delete_nth_from_end(&list_del, 2); // 末尾から2番目(4)を削除
    print_list("After deleting 2nd from end (4)", list_del);
    
    delete_nth_from_end(&list_del, 4); // 末尾から4番目(1)を削除
    print_list("After deleting 4th from end (1)", list_del);
    
    delete_nth_from_end(&list_del, 1); // 末尾から1番目(5)を削除
    print_list("After deleting 1st from end (5)", list_del);

    // メモリ解放（追加分も解放が必要だが、ここでは省略）

    // メモリ解放（省略）

    return 0;
}