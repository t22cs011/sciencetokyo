/* ヒープにおけるDELETEMINとINSERTのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500                 /* 配列Aの最大サイズ */
/* 関数の宣言 */
void insert(int x, int *A, int *n);
int deletemin(int *A, int *n);
void upmin(int i, int *A, int n);
void downmin(int i, int *A, int n);
void swap(int i, int j, int *A);

main()
/* ヒープA[0],...,A[n-1]に対するテストプログラム */
{
 int A[N];
 int n, i, k, min;

 n=0;
 for(k=0; k<10; k++) 
   {
    insert(100-(5-i)*(5-i), A, &n);
    printf("n = %d\nA = ", n);
    for(i=0; i<n; i++) printf("%d ",A[i]);
    printf("\n");
   }
 for(k=0; k<10; k++) 
   {
    min=deletemin(A, &n);
    printf("n = %d, min = %d\nA = ", n, min);
    for(i=0; i<n; i++) printf("%d ",A[i]);
    printf("\n");
   }
 return(0);
}

void insert(int x, int *A, int *n)
/* ヒープA[0],...,A[n-1]へ新しい要素xの挿入; n=n+1 */
{
 int n1;

 n1=*n;                          /* nの値を仮置き */
 if(n1>=N) {printf("Error: Heap A is full.\n"); exit(1);}
                                 /* 誤りチェック: Aは満杯 */
 A[n1]=x;                        /* 末尾へｘを置く */
 upmin(n1, A, n1+1);             /* 上への修正 */
 *n=n1+1;                        /* nの更新 */
 return;
}

int deletemin(int *A, int *n)
/* ヒープA[0],...,A[n-1]から最小要素A[0]の出力と除去; n=n-1 */
{
 int min, n1;

 n1=*n;                           /* nの値を仮置き */
 if(n1<1) {printf("Error: Heap is empty.\n"); exit(1);} /* 誤: Aは空 */
 min=A[0]; A[0]=A[n1-1];          /* A[0]の出力とA[n-1]の移動 */
 if(n1>1) downmin(0, A, n1-1);    /* ヒープ条件の回復のため下へ */
 *n=n1-1;                         /* nの更新 */
 return(min);
}

void upmin(int i, int *A, int n)
/* A[i]から上方へ、ヒープ条件回復のためswap操作を適用 */
{
 int j;

 if(i<0 || i>=n)                 /* 誤りチェック */
   {printf("Illegal element i=%d for n=%d\n", i, n); exit(1);}
 if(i==0) return;                /* 根へ到達すれば終了 */
 j=(i-1)/2;                      /* iの親 */
 if(A[j]>A[i])                   /* iとjの交換 */
   {
    swap(i, j, A); 
    upmin(j, A, n);              /* jの上方へ再帰的実行 */
   }
 return;
}

void downmin(int i, int *A, int n)
/* A[i]から下方へ、ヒープ条件回復のためのswap操作を適用 */
{
 int j;

 if(i<0 || i>=n)                 /* 誤りチェック */
   { printf("Illegal element i=%d for n=%d\n", i, n); exit(1);}
 j=2*i+1;                        /* iの左の子 */
 if(j>=n) return;
 if(j+1<n && A[j]>A[j+1]) j=j+1; /* j: iの子で小さな値を持つ方 */
 if(A[j]<A[i])                   /* iとjの交換 */
   {
    swap(i, j, A);
    downmin(j, A, n);            /* jの下方へ再帰的実行 */
   }
 return;
}

void swap(int i, int j, int *A)
/* A[i]とA[j]の交換 */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}