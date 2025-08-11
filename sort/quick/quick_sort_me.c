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
    int i = low - 1;
    int mid = (low + high) / 2;
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
    int v = partition(a, low, high);
    quick_sort(a, low, v - 1);
    quick_sort(a, v + 1, high);
}


void sort_array(int a[], int low, int high){
    return quick_sort(a, 0, high);
}

int main() {   // カウンターをリセット
    // --- クイックソート(Lomuto方式) ---
    int c[] = {9, 8, 5, 1, 2};
    int n = 5;

    printf("クイックソート前: ");
    print_array("c", c, n);

    sort_array(c, 0, n - 1);
    
    printf("クイックソート後: ");
    print_array("c", c, n);

    return 0;
}


// int partition(int a[], int low, int high){
    //     int i = low - 1;
    //     int pivot = a[high];
    //     for(int j = low; j < high; j++){
    //         if(a[j] <= pivot){
    //             i++;
    //             swap(&a[i], &a[j]);
    //         }
    //     }
    //     swap(&a[i + 1], &a[high]);
    //     return i + 1;
    // }
    
    // void quick_sort(int a[], int low, int high){
    //     if(low >= high) return;
    //     int p = partition(a, low, high);
    //     quick_sort(a, low, p - 1);
    //     quick_sort(a, p + 1, high);
    // }
    
    // void sort_array(int a[], int low, int high){
    //     quick_sort(a, low, high);
    // }
    