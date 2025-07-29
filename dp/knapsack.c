#include<stdio.h>
#define N 3 // 配列 num_list の要素数
#define MAX_NUM 10 // MAX_NUM 以内の最大値を求める
 
int find_max_dp(int num_list[N]) {
    int tmp_choice, tmp_not_choice;
    int table[N][MAX_NUM+1];
 
    // DP表の一番上（i = 0）を初期化
    for(int j = 0; j <= MAX_NUM; j += 1) {
        if(num_list[0] > j) {
            table[0][j] = 0; // 何も入れられないとき
        }
        else {
            table[0][j] = num_list[0]; // 0番目の数字を足せるとき
        }
    }
    
    for(int i = 1; i < N; i += 1) {
        for(int j = 0; j <= MAX_NUM; j += 1) {
            tmp_not_choice = table[i-1][j];
            if(num_list[i] > j) {
                table[i][j] = tmp_not_choice;
            }
            else {
                tmp_choice = table[i-1][j - num_list[i]] + num_list[i];
                if(tmp_choice >= table[i-1][j])
                    table[i][j] = tmp_choice;
                else
                    table[i][j] = tmp_not_choice;
            }
        }
    }
 
    // 最適解の復元
    printf("選んだ要素: ");
    int i = N-1, j = MAX_NUM;
    while(i >= 0) {
        if(i == 0) {
            if(j >= num_list[0] && table[0][j] == num_list[0]) {
                printf("%d ", num_list[0]);
            }
            break;
        }
        
        if(j >= num_list[i] && table[i][j] == table[i-1][j - num_list[i]] + num_list[i]) {
            printf("%d ", num_list[i]);
            j -= num_list[i];
        }
        i--;
    }
    printf("\n");
 
    return table[N-1][MAX_NUM];
}
 
int main() {
    int num_list[N] = {4,8,6};
 
    int ans = find_max_dp(num_list);
    printf("%2dに最も近い選び方1：%2d\n",MAX_NUM,ans);
 
    return 0;
}