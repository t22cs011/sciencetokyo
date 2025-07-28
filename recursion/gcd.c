#include <stdio.h>  // printfなどの標準入出力関数を使用
#include <stdlib.h> // malloc, exitなどの標準ライブラリ関数を使用

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    int a = 48, b = 18;
    
    printf("%dと%dの最大公約数は: %d\n", a, b, gcd(a, b));
    
    // 他の例も試してみる
    printf("12と8の最大公約数は: %d\n", gcd(12, 8));
    printf("54と24の最大公約数は: %d\n", gcd(54, 24));
    printf("7と13の最大公約数は: %d\n", gcd(7, 13));

    return 0;
}