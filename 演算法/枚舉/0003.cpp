/*    Repeatless Numbers
 *    URL : http://poj.org/problem?id=2956
 *
 *    Language: G++
 *    *有scanf()就要用C++,不能用G++,不然在POJ上會Compile Error
 *    *在C++上有Runtime Error,但是local卻不會有,可以換成G++試試看
 *
 *    1. 可以利用暴力解來映證答案
 *    2. 利用NoRepeat table記錄所有不是repeat number
 *    3. 將個位數1~9放到NoRepeat table後開始檢查不同base加上NoRepeat table產生的數字
 *       如果是答案就放到NoRepeat table
 *    4. Ex:
 *       NoRepeat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}
 *       base = 10 :
 *           檢查 (10+1), (10+2), (10+3), ... ..., (10+9)
 *       base = 20, 30, ...90:
 *           相同作法
 *       base = 100 :
 *           檢查 (100+1), (100+2), (100+3), ..., (100+10), (100+12), (100+13), ..., (100+98)
 *       base = 200~900:
 *           相同作法
 */

#include <iostream>
//#include <ctime>
using namespace std;

//#define  DBG
//#define BRUTEFORCE
#define NUMS 1000000
int NoRepeat[NUMS];

#ifdef BRUTEFORCE  // 暴力解 : 檢查所有數字  ==> TLE
void CreateNoRepeatTable()
{
    int index = -1;
    int i = 1, j;
    int digits;

    while (index<NUMS) {
        j = i;
        digits = 0;
        while (j>0) {
            int d = j - (j/10)*10;
            if ((digits >> d) & 0x1 == 1)
                break;
            else {
                j /= 10;
                digits |= (1 << d);
            }
        }
        if (j == 0) {
            NoRepeat[++index] = i;
        }
        ++i;
    }
}
#else
void CreateNoRepeatTable()
{
    int i, j, tmp;
    int index;  /* NoRepeat table的index */
    int upper, upper10, upper100; /* upper表示加入小於目前位數的邊界 ; upper10 = upper/10 ; upper100 = upper/10 */
    int base;  /* 以base為基數, 然後去加上小於upper的數字*/
    int digits; /* 用來記錄digits 0~9是否有出現過 */

    /* 將個位數 1~9放到NoRepeat table */
    for (i = 0; i<9; ++i)
        NoRepeat[i] = i+1;

    index = 8;
    upper = 10;

    while (1) {
        /* 產生10~90 , 100~900 , 1000~9000 , 10000~90000 ... ... */
        for (i = 1; i<10; ++i) {
            j = 0;
            upper10 = upper/10;
            upper100 = upper/100;
            base = i*upper;

            /*  先將base放到NoRepeat table然後再檢查以base為基數加上NoRepeat裡面的數字所產生的數字
             *  排除100~900, 1000~9000 , 10000~90000 ...有2個0的數字
             */
            if (base < 100)
                NoRepeat[++index] = base;

            /* Ex:當base為10~90 , upper為10 ==> 因為10~90可以搭配1~9產生新的數字
             *    當base為100~900 , upper為100 ==> 因為100~900可以搭配1~99產生新的數字
             * 因此在NoRepat table裡面的數字必須小於upper然後跟base產生新的數字
             */
            while (NoRepeat[j] < upper) {
                /*  需要考慮到base在1000以後可能有1002, 1003, 1004, 1005, ..., 1009
                 *  中間的0沒辦法檢查到
                 *  upper100 >=10  ==>  表示base為1000之後的情況
                 *  如果此時NoRepeat[j] 又小於upper100, 則會有中間是0的情況,此時就跳過不檢查
                 */
                if (upper100 >=10 && NoRepeat[j] < upper100) {
                    ++j;
                    continue;
                }

                digits = 0;
                tmp = NoRepeat[j];
                digits |= (1 << i);

                /* 需要考慮到base在1000以後可能有1020, 1030, 1040, 1050, 1060, ..., 1090
                 * 中間的0沒辦法檢查到
                 * tmp < upper10  ==> 表示中間會有一個0 , 因此需要紀錄有0出現
                 */
                if (tmp < upper10)
                    digits |= 0x1;

                while (tmp > 0) {
                    int d = tmp % 10;
                    if ((digits >> d) & 0x1 == 1) // 檢查是否有出現過該數字
                        break;
                    digits |= (1 << d);
                    tmp /= 10;
                }
                if (tmp == 0) {
                    NoRepeat[++index] = base + NoRepeat[j];
                    if (index == NUMS)
                        return;
                }
                ++j;
            }
        }
        upper *= 10;
    }
}
#endif

int main()
{
    int n;
#ifdef DBG
    clock_t start, end;
    float t_used;
    start = clock();
#endif
    CreateNoRepeatTable();
#ifdef DBG
    end = clock();
    t_used = (float) (end-start)/CLK_TCK;
    cout << "Spend " << t_used << " sec" << endl;
    for (int i = 0;i < NUMS; ++i)
        cout << NoRepeat[i] << endl;
#endif
    while ((cin >> n) && n!=0) {
        cout << NoRepeat[n-1] << endl;
    }
    return 0;
}