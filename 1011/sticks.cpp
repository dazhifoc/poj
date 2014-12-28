// 五 12/26 20:09:20 2014
//

#include <iostream>
#include <iomanip>
#include <stdlib.h>
int join_sticks(int num, int* sticks);
int cmp ( const void *a , const void *b );
bool check_len(int len, int num, int* sticks, int* mark);
bool pk_stick(int len, int num, int* sticks, int* mark, int remain, int head);
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
            int mark[64] = {0};
            for (int i = 0; i < num; i++) {
                sticks_cp[i] = sticks[i];
            }
            if (check_len(i, num, sticks_cp, mark)){
                return i;
            }
            // std::cout << std::endl; // test
        }
    }
    // test
    return sum;
}
bool check_len(int len, int num, int* sticks, int* mark_pre)
{
    // std::cout<< "check_len" << std::endl;
    int mark[64];
    for (int i = 0; i < num; i++) {
        mark[i] = mark_pre[i];
    }
    int head = -1;
    for (int i = 0; i < num; i++) {
        if(mark[i] == 0){
            head = i;
            break;
        }
    }
    if(head == -1){
        return true;
    }
    // std::cout << sticks[head] << " ";       // test
    int remain = len - sticks[head];        //第一根棍子一定要用最大的
    mark[head] = 1;                         // 标记被用了
    bool result =  pk_stick(len, num, sticks, mark, remain, head + 1);
    return result;
}
int cmp ( const void *a , const void *b )
{
    return *(int *)b - *(int *)a;
}
bool pk_stick(int len, int num, int* sticks, int* mark_pre, int remain, int head)
{
    int mark[64];
    for (int i = 0; i < num; i++) {
        mark[i] = mark_pre[i];
    }
    if(remain == 0){
        // std::cout << std::endl;
        // for (int i = 0; i < num; i++) {
        //     std::cout<<std::setw(2) << sticks[i];
        // }
        // std::cout << std::endl;
        // for (int i = 0; i < num; i++) {
        //     std::cout <<std::setw(2)<<mark[i];
        // }
        // std::cout << std::endl;
        return check_len(len, num, sticks, mark);
    }
    // 选择一下个棍子
    for (int i = head; i < num; i++) {
        if(remain >= sticks[i] and mark[i] == 0){
             mark[i] = 1;
             // std::cout<< sticks[i] << " ";
             bool result =  pk_stick(len, num, sticks, mark, remain - sticks[i], i +1);
             if(result){
                 return true;
             }
             else{
                 mark[i] = 0;
                 while (sticks[i]==sticks[i+1]) {
                     i++;
                 }
                 ;               // next try
             }
        }
    }
    // std::cout<< "no fit stick"<<std::endl;
    return false;
}
