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
    vector<int> get_mlen();
};
void D2vector::push(int val)
{
    if(m_coms.size() == 0){
        vector<int> seq;
        seq.push_back(val);
        m_coms.push_back(seq);
    }
    else{
        dvect::iterator push_candidate = m_coms.end();
        int candidate_len = 0;
        for (dvect::iterator pos = m_coms.begin(); pos < m_coms.end(); pos++) {
            if(val > pos->back() and pos->size() > candidate_len ){
                candidate_len = pos->size();
                push_candidate = pos;
            }
        }
        if(push_candidate == m_coms.end()){
            vector<int> seq;
            seq.push_back(val);
            m_coms.push_back(seq);
        }
        else{
            vector<int> seq(*push_candidate);
            seq.push_back(val);
            m_coms.push_back(seq);
        }
    }
}
vector<int> D2vector::get_mlen()
{
    dvect::iterator push_candidate = m_coms.end();
    int candidate_len = 0;
    for (dvect::iterator pos = m_coms.begin(); pos < m_coms.end(); pos++) {
        if(pos->size() > candidate_len ){
            candidate_len = pos->size();
            push_candidate = pos;
        }
    }
    if(push_candidate == m_coms.end()){
        return vector<int>();
    }
    else{
        return *push_candidate;
    }
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
    D2vector* dp[M+1][M+1];
    D2vector* result = new D2vector[num[A] + num[B] + 1];
    D2vector* iter = result;
    for (int j = 0; j <= num[B]; j++) {
        dp[0][j] = iter++;
    }
    for (int i = 1; i <= num[A]; i++) {
        dp[i][0] = iter++;
    }
    for (int i = 1; i <= num[A]; i++) {
        for (int j = 1; j <= num[B]; j++) {
            if(seq[A][i-1] == seq[B][j-1]){
                // 逻辑有问题, 指针传递, 会使后面的结果覆盖前面, 影响别外的传递路线
                dp[i][j] = dp[i-1][j-1];
                dp[i][j] -> push(seq[A][i-1]);
            }
            else{
                if((dp[i][j-1] -> get_mlen()).size() > (dp[i-1][j] -> get_mlen()).size()){
                    dp[i][j] = dp[i][j-1];
                }
                else
                    dp[i][j] = dp[i-1][j];
            }
        }

    }
    D2vector* max_result = result;
    vector<int>::size_type max_length = (result -> get_mlen()).size();
    for (int i = 1; i < num[A] + num[B] -1; i++) {
        if(result[i].get_mlen().size() > max_length){
            max_length = result[i].get_mlen().size();
            max_result = &result[i];
        }
    }
    cout << max_length << endl;
    vector<int> max_seq = max_result -> get_mlen();
    copy(max_seq.begin(), max_seq.end(), ostream_iterator<int>(cout," "));
    cout << endl;
    delete [] result;
    return 0;
}
