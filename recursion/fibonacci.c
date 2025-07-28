#include <stdio.h>  // printfなどの標準入出力関数を使用
#include <stdlib.h> // malloc, exitなどの標準ライブラリ関数を使用

int fibonacci(int n)
{
    if(n <= 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(){
    int num = 6; // フィボナッチ数列の5番目の数: 0,1,1,2,3,5,8
    
    // 最初の10個のフィボナッチ数列を表示
    printf("最初の%d個のフィボナッチ数列: ", num);
    printf("%d ", fibonacci(num));

    printf("\n");
    
    return 0;
}