#include <stdio.h>  // printfなどの標準入出力関数を使用

int factorial(int n)
{
    if(n == 1) return 1;
    return n * factorial(n - 1);
}

int main()
{
    int num = 6;
    printf("factorial of %d is %d", num, factorial(num));
    return 0;
}