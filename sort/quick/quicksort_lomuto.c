//クイックソートのLomuto方式による実装
#include <stdio.h>

// 配列の内容を出力するヘルパー関数
void print_array(const char *name, int a[], int n) {
    printf("%s: {", name);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(int a[], int low, int high){
    int mid = (low + high) / 2;
    int i = low - 1;
    int pivot = a[high];

    for(int j = low; j < high; j++){
        if(a[j] <= pivot){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void quick_sort(int a[], int low, int high){
    if(low >= high) return;
    int p = partition(a, low, high);
    quick_sort(a, low, p - 1);
    quick_sort(a, p + 1, high);
}

void sort_array(int a[], int low, int high){
    return quick_sort(a, 0, high - 1);
}


int main() {   // カウンターをリセット
    // --- クイックソート(Lomuto 最後がpivot) ---
    int c[] = {9, 8, 5, 1, 2};
    int n = 5;

    printf("クイックソート前: ");
    print_array("c", c, n);

    quick_sort(c, 0, n - 1);
    
    printf("クイックソート後: ");
    print_array("c", c, n);

    return 0;
}