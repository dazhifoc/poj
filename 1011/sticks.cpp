// 五 12/26 20:09:20 2014
//

#include <iostream>
#include <stdlib.h>
int join_sticks(int num, int* sticks);
int cmp ( const void *a , const void *b );
bool check_stick(int len, int num, int* sticks);
int main(int argc, char *argv[])
{
    int num;
    int sticks[64];
    std::cin >> num;
    while (num) {
        for (int i = 0; i < num; i++) {
            std::cin >> sticks[i];
        }
        std::cout << join_sticks(num, sticks) << std::endl;
        std::cin >> num;
    }
    return 0;
}
int join_sticks(int num, int* sticks)
{
    qsort(sticks, num, sizeof(int), cmp);
    // test
    int sum = 0;
    for (int i = 0; i < num; i++) {
        sum += sticks[i];
    }
    int maxs = sum;             // 一根棍子长
    int mins = sticks[0];       // 比最小的长
    // 测试整除
    for (int i = mins; i < maxs; i++) {
        int a = sum / i;
        if(a * i == sum){
            std::cout << i << std::endl;
            int sticks_cp[64];
            for (int i = 0; i < num; i++) {
                sticks_cp[i] = sticks[i];
            }
            if (check_stick(i, num, sticks_cp)){
                return i;
            }
            std::cout << std::endl;
        }
    }
    // test
    return sum;
}
bool check_stick(int len, int num, int* sticks)
{
    std::cout << sticks[0] << " ";
    int remain = len - sticks[0]; //
    sticks[0] = 0;
    int count = 1;
    for (int i = 1; i < num; i++) {
        if(remain >= sticks[i]){
            remain = remain - sticks[i];
            std::cout << sticks[i] << " ";
            sticks[i] = 0;
            count++;
        }
    }
    if(remain == 0){
        std::cout << std::endl;
        qsort(sticks, num, sizeof(int), cmp);
        if(sticks[0] == 0){
            return true;
        }
        return check_stick(len, num - count, sticks);
    }
    else
        std::cout << remain << std::endl;
        return false;
}
int cmp ( const void *a , const void *b )
{
    return *(int *)b - *(int *)a;
}
