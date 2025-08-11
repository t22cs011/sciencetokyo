#include <stdio.h>

// 配列の要素をきれいに表示するためのヘルパー関数
void print_array(const char* label, int arr[], int size) {
    printf("%s: [ ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int mergesort(int a[], int begin, int end, int w[]){
    //base-case
    if(begin >= end) return 0;
    
    //merge
    int mid = (begin + end) / 2;
    int i = begin;
    int j = mid + 1;
    int k;

    mergesort(a, begin, mid, w);
    mergesort(a, j, end, w);

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

    return 0;
}

int main() {
    int a[] = {3, 5, 1, 4, 2};
    int n = sizeof(a) / sizeof(a[0]);
    int w[n];

    print_array("Before", a, n);

    // マージソートを実行し、比較回数を受け取る
    int count = mergesort(a, 0, n - 1, w);

    print_array("After ", a, n);
    printf("Comparisons: %d\n", count); // 比較回数を表示

    return 0;
}