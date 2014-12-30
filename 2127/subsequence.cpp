// Tue 30 Dec 2014 09:30:44 AM HKT
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
#define M 500
#define A 0
#define B 1
typedef vector<vector<int> > dvect;
int seq[2][M];
// 存储最大公共子序列的容器
bool more_vectors(const vector<int>& a,const vector<int>& b) {
    return a.size() > b.size();
}
class D2vector
{
private:
    dvect m_coms;
public:
    D2vector(){};
    ~D2vector(){};
    void push(int val);
    vector<int>::size_type get_mlen();
    vector<int> get_seq();
};
void D2vector::push(int val)
{
    if(m_coms.size() == 0){
        vector<int> seq;
        seq.push_back(val);
        m_coms.push_back(seq);
    }
    else{
        // 假设子序列按元素多少排列,一量新元素加到大子序列上,
        // 小子序列就没有存在的意义,可以直接丢弃
        dvect::iterator pos = m_coms.begin();
        for (; pos < m_coms.end(); pos++) {
            if(val > pos->back() ){
                pos->push_back(val);
                break;
            }
        }
        if(m_coms.end() == pos){
            vector<int> seq;
            seq.push_back(val);
            m_coms.push_back(seq);
        }
        else{
            m_coms.erase(pos + 1, m_coms.end());
            // 排序,保证按元素多少排列
            sort(m_coms.begin(),m_coms.end(),more_vectors);
        }
    }
}
vector<int>::size_type D2vector::get_mlen()
{
    if(m_coms.size() == 0){
        return 0;
    }
    else
        return m_coms.begin()->size();
}
vector<int> D2vector::get_seq()
{
    if(m_coms.size() == 0){
        return vector<int>();
    }
    else
        return m_coms.front();

}
int main(int argc, char *argv[])
{
    int num[2];
    for (int i = 0; i < 2; i++) {
        cin >> num[i];
        for (int j = 0; j < num[i]; j++) {
            cin >> seq[i][j];
        }
    }
    D2vector* dp[M][M];
    D2vector* result = new D2vector[num[A] + num[B] -1];
    D2vector* iter = result;
    for (int j = 0; j < num[B]; j++) {
        dp[0][j] = iter++;
        if(seq[A][0] == seq[B][j]){
            dp[0][j] -> push(seq[A][0]);
        }
    }
    for (int i = 1; i < num[A]; i++) {
        dp[i][0] = iter++;
        if(seq[B][0] == seq[A][i]){
            dp[i][0] -> push(seq[B][0]);
        }
    }
    for (int i = 1; i < num[A]; i++) {
        for (int j = 1; j < num[B]; j++) {
            if(seq[A][i] == seq[B][j]){
                dp[i][j] = dp[i-1][j-1];
                dp[i][j] -> push(seq[A][i]);
            }
            else{
                if(dp[i][j-1] -> get_mlen() > dp[i-1][j] -> get_mlen()){
                    dp[i][j] = dp[i][j-1];
                }
                else
                    dp[i][j] = dp[i-1][j];
            }
        }

    }
    D2vector* max_result = result;
    vector<int>::size_type max_length = result -> get_mlen();
    for (int i = 1; i < num[A] + num[B] -1; i++) {
        if(result[i].get_mlen() > max_length){
            max_length = result[i].get_mlen();
            max_result = &result[i];
        }
    }
    cout << max_length << endl;
    vector<int> max_seq = max_result -> get_seq();
    copy(max_seq.begin(), max_seq.end(), ostream_iterator<int>(cout," "));
    cout << endl;
    delete [] result;
    return 0;
}
