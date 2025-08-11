#include <stdio.h>
#include <string.h> // 配列のコピーにmemcpyを使用

// 配列の内容を表示するためのヘルパー関数
void print_array(const char* label, int arr[], int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * プログラム 3.1: バブルソート (Bubble Sort)
 * 空欄 A の答え: バブルソート
 */
void sort_a(int a[], int n) {
    int i, j, tmp;
    for (i = 0; i < n - 1; ++i) {
        for (j = n - 1; i < j; --j) {
            if (a[j] < a[j-1]) {
                tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
    }
}

/*
 * プログラム 3.2: 挿入ソート (Insertion Sort)
 * 空欄 B の答え: 挿入ソート
 */
void sort_b(int a[], int n) {
    int i, j, tmp;
    for (j = 1; j < n; ++j) {
        tmp = a[j];
        i = j - 1;
        while (0 <= i && tmp < a[i]) {
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = tmp;
    }
}

/*
 * プログラム 3.3: マージソート (Merge Sort)
 */
int mergesort(int a[], int begin, int end, int w[]){
    //base-case
    if(begin >= end) return 0;
    
    //merge
    int mid = (begin + end) / 2;
    int i = begin;
    int j = mid + 1;
    int k;
    int c;

    c += mergesort(a, begin, mid, w);
    c += mergesort(a, j, end, w);

    for(int k = begin; k <= end; k++){
        if(i > mid){
            w[k] = a[j++];
        }
        else if(j > end){
            w[k] = a[i++];
        }
        else{
            if(a[i] < a[j]) w[k] = a[i++];
            else w[k] = a[j++];
        }
    }


    for(k = begin; k <= end; k++){
        a[k] = w[k];
    }

    return c;
}


int main() {
    int original_array[] = {8, 4, 3, 7, 6, 1, 2, 5};
    int n = sizeof(original_array) / sizeof(original_array[0]);
    int c = 0;

    int array_a[n];
    int array_b[n];
    int array_c[n];
    int work_array[n]; // マージソート用の作業配列

    printf("元の配列\n");
    print_array("Initial", original_array, n);
    printf("\n----------------------------------------\n\n");

    // --- バブルソート (sort_a) のテスト ---
    printf("プログラム 3.1: バブルソート (sort_a)\n");
    memcpy(array_a, original_array, sizeof(original_array));
    print_array("ソート前", array_a, n);
    sort_a(array_a, n);
    print_array("ソート後", array_a, n);
    printf("\n----------------------------------------\n\n");

    // --- 挿入ソート (sort_b) のテスト ---
    printf("プログラム 3.2: 挿入ソート (sort_b)\n");
    memcpy(array_b, original_array, sizeof(original_array));
    print_array("ソート前", array_b, n);
    sort_b(array_b, n);
    print_array("ソート後", array_b, n);
    printf("\n----------------------------------------\n\n");

    // --- マージソート (mergesort) のテスト ---
    printf("プログラム 3.3: マージソート (mergesort)\n");
    memcpy(array_c, original_array, sizeof(original_array));
    print_array("ソート前", array_c, n);
    c = mergesort(array_c, 0, n - 1, work_array);
    print_array("ソート後", array_c, n);
    printf("\n----------------------------------------\n\n");
    printf("要素の比較回数: %d", c);

    return 0;
}