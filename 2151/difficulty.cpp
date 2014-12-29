// 日 12/28 17:26:41 2014
#include <iostream>
#include <iomanip>
#define M 30
#define T 1000
using namespace std;
double check_difficulty(double p[T][M], int t, int m, int n){
    // 每队分别计算
    double dp[T][M+1][M+1] = {0};
    for (int team = 0; team < t; team++) {
        double *p_each = &p[team][0];
        // dp[team][0][0],表示共0题,做对0题的的概率 = 1
        dp[team][0][0] = 1;
        // dp[team][j][k],表示共j题,做对k题
        for (int j = 1; j <= m; j++) {
            // 都没做对,j-1个问题中做对0个,第j个也没做对
            dp[team][j][0] = dp[team][j-1][0] * (1-p_each[j-1]);
            for (int k = 0; k <= m; k++) {
                // j-1个中做对k个,第j个没做对,j-1个中做对k-1个,第j个做对
                dp[team][j][k] = dp[team][j-1][k] * (1-p_each[j-1]) + dp[team][j-1][k-1] * p_each[j-1];
            }
        }
    }
    // 每队至少答对一题
    double least1 = 1;
    for (int team = 0; team < t; team++) {
        least1 *= (1 - dp[team][m][0]);
    }
    // 每队做对1~n-1
    double one_to_n = 1;
    for (int team = 0; team < t; team++) {
        double one_team = 0;
        for (int k = 1; k < n; k++) {
            one_team += dp[team][m][k];
        }
        one_to_n *= one_team;
    }
    return least1 - one_to_n;
}
int main(int argc, char *argv[])
{
    int m;                      // (0 < M <= 30), T (1 < T <= 1000) and N (0 < N <= M).
    int t;
    int n;
    double p[T][M];
    cin >> m >> t >> n;
    while(m){
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < m; j++) {
                cin >> p[i][j];
            }
        }
        cout << setprecision(3) <<check_difficulty(p,t,m,n) << endl;
        cin >> m >> t >> n;
    }
    return 0;
}
