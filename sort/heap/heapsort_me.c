#include <stdio.h>

// プロトタイプ宣言
void heapify(int a[], int i, int j);
void build_heap(int a[], int m);
void heapsort(int a[], int m);
void swap(int a[], int i, int j);
void print_array(const char *label, int a[], int m);

// a[i]とa[j]の値を交換する
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void heapify(int a[], int i, int j){
    int k;
    while((k = 2 * i + 1) <= j){
        if(k < j && a[k] < a[k + 1]){
            k++;
        }
        if(a[i] >= a[k]){
            break;
        }
        swap(a, i, k);
        i = k;
    }
}

void build_maxheap(int a[], int m){
    int i;
    for(i = m / 2 - 1; i >= 0; i--){
        heapify(a, i, m - 1);
    }
}

void heapsort(int a[], int m){
    heapify(a, 0, m);
    while(m > 1){
        swap(a, 0, m - 1);
        heapify(a, 0, m - 2);
        m--;
    }
}

// 配列の内容を表示する
void print_array(const char *label, int a[], int m) {
    printf("%s: ", label);
    for (int i = 0; i < m; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main() {
    int a[] = {5, 2, 7, 3, 6, 1, 4}; // テスト用のデータ
    int m = sizeof(a) / sizeof(a[0]); // 配列の要素数

    print_array("Original array", a, m); // ソート前の配列を表示

    heapsort(a, m); // ヒープソートを実行

    print_array("Sorted array  ", a, m); // ソート後の配列を表示

    return 0;
}
