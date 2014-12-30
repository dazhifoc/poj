// Tue 30 Dec 2014 09:30:44 AM HKT
#include <iostream>
using namespace std;
#define M 500
#define A 0
#define B 1
int seq[2][M];
int result[M];
int main(int argc, char *argv[])
{
    int num[2];
    for (int i = 0; i < 2; i++) {
        cin >> num[i];
        for (int j = 0; j < num[i]; j++) {
            cin >> seq[i][j];
        }
    }
    // 记录有序最长子序列个数
    int count_dp[M][M] = {0};
    // 记录有序最长子序列最后的值
    int last_dp[M][M];
    for (int j = 0; j < num[B]; j++) {
        if(seq[A][0] == seq[B][j]){
            count_dp[0][j] = 1;
            last_dp[0][j] = seq[A][0];
        }
        else
            count_dp[0][j] = 0;

    }
    for (int i = 0; i < num[B]; i++) {
        if(seq[B][0] == seq[A][i]){
            count_dp[i][0] = 1;
            last_dp[i][0] = seq[B][0];
        }
        else
            bcount_dp[i][0] = 0;
    }


    return 0;
}
