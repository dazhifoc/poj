// 一 12/29 22:10:59 2014
#include <iostream>
#include <algorithm>
#include <vector>
typedef unsigned int uint;
typedef long long unsigned int lluint;
using namespace std;
int main(int argc, char *argv[])
{
    uint num;
    cin >> num;
    std::vector<uint> planks(num);
    for (int i = 0; i < num; i++) {
        cin >> planks[i];
    }
    sort(planks.begin(), planks.end(), less<uint>());
    lluint cost = 0;
    for (int i = 0; i < num - 1; i++) {
        uint sum = planks[0] + planks[1];
        cost += sum;
        planks.insert(lower_bound(planks.begin() + 2, planks.end(), sum), sum);
        planks.erase(planks.begin(), planks.begin() + 2);
    }
    cout << cost <<endl;
    return 0;
}
