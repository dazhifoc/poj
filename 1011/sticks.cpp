// 五 12/26 20:09:20 2014
//

#include <iostream>
#include <stdlib.h>
int join_sticks(int num, int* sticks);
int cmp ( const void *a , const void *b );
bool check_len(int len, int num, int* sticks);
bool pk_stick(int num, int* sticks, int remain, int head, int &count);
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
            // std::cout << "try:"<< i << std::endl; // test
            int sticks_cp[64];
            for (int i = 0; i < num; i++) {
                sticks_cp[i] = sticks[i];
            }
            if (check_len(i, num, sticks_cp)){
                return i;
            }
            // std::cout << std::endl; // test
        }
    }
    // test
    return sum;
}
bool check_len(int len, int num, int* sticks)
{
    // std::cout << sticks[0] << " ";          // test
    int remain = len - sticks[0]; //第一根棍子一定要用最大的
    sticks[0] = 0;
    int count = 1;
    int head = 1;
    bool result = pk_stick(num, sticks, remain, head, count);

    if(result){
        // std::cout << std::endl;               // test
        qsort(sticks, num, sizeof(int), cmp);    // 贪心,成功拼接的棍子不会拆开
        if(sticks[0] == 0){
            return true;
        }
        return check_len(len, num - count, sticks);
    }
    else
        //        std::cout << remain << std::endl;
        return false;
}
int cmp ( const void *a , const void *b )
{
    return *(int *)b - *(int *)a;
}
bool pk_stick(int num, int* sticks, int remain, int head, int &count)
{
    if(remain == 0){
        return true;
    }
    // 选择一下个棍子
    for (int i = head; i < num; i++) {
        if(remain >= sticks[i]){
            bool one_try =  pk_stick(num, sticks, remain - sticks[i], i +1, count);
            if(one_try){
                // std::cout << sticks[i] << " "; // test
                sticks[i] = 0; // 被用了
                count++;
                return true;
            }
            else{
                while (sticks[i]==sticks[i+1]) {
                    i++;
                }
                ;               // next try
            }
        }
    }
    return false;
}
