// 日 12/28 17:26:41 2014
#include <iostream>
#define M 30
#define T 1000
using namespace std;
double check_difficulty(double p[T][M], int t, int m){
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < m; j++) {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
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
        cout << check_difficulty(p,t,m) << endl;
        cin >> m >> t >> n;
    }
    return 0;
}
