#include <stdio.h>

void f1(int na, int a[], int nb, int b[]){
    int i, j, k;
    for(i = 0; i < na; i++){
        for(j = nb - 1; j >= 0; j--){
            if(b[j] > a[i]){
                break;
            }
        }
        if(j < nb - 1){
        for(k = nb - 2;  k > j; k--){
            b[k + 1] = b[k];
        }
        b[j + 1] = a[i];
        }
    }
}

void f2(int na, int a[], int nb, int b[]){
    int i, j, k;
    for(i = 0; i < na; i++){
        for(j = 0; j < nb; j++){
            if (a[i] > b[j]) {
                for (k = nb - 1; k > j; k--) {
                    b[k] = b[k - 1];
                }
                b[j] = a[i];
                break;
            }
        }
    }
}

// // 配列の要素を画面に出力する関数
// void print_array(int b[], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d ", b[i]);
//     }
//     printf("\n");
// }


int main(){
    int a[] = {2, 17, 12, 4, 6, 19, 10, 13, 12, 7};
    int b[] = {0, 0, 0, 0, 0};
    f2(10, a, 5, b);
    for (int t = 0;t <= 4;t++){
        printf("%d ",b[t]);
    }
    return 0;
}