/*    The Pilots Brothers' refrigerator
 *    URL : http://poj.org/problem?id=2965
 *
 *    Language: G++
 *    *有scanf()就要用C++,不能用G++,不然在POJ上會Compile Error
 *    *在C++上有Runtime Error,但是local卻不會有,可以換成G++試試看
 *
 *    1. 將input轉成0/1然後儲存在int裡面,每一個bit代表每一個輸入的狀態
 *       例如: -+--        0100                            0  1  2  3
 *             ----   ==>  0000  對應到int每個位元位置 ==>  4  5  6  7
 *             ----        0000                            8  9 10 11
 *             -+--        0100                           12 13 14 15
 *    2. 一共有16個,因此共有2^16種可能
 *       因為所有枚舉不多,因此用枚舉方法來解
 *    3. 當i的bit為1,表示該位置需要做更動,因此同一個row和col全都要一起更動
 *       但是要注意到如果一個一個改動的話會超時,因此需要用到XOR來一次更改整個row/col
 *    4. 當每個i檢查完時,看看ChangedStatus的值是全部bit為0
 */

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char input[4][5];
    int Steps[16][2], TmpSteps[16][2];
    int Index, TmpIndex;
    int OriginStatus, ChangedStatus;
    int i, j, k;
    int count, minimun;

    while (cin >> input[0] >> input[1] >> input[2] >> input[3]) {
        OriginStatus = 0;
        minimun = 17;

        /* 將input儲存在int裡 */
        for (i = 0; i<4; ++i) {
            for (j = 0; j<4; ++j) {
                if (input[i][j] == '+') {
                    OriginStatus |= ( 1 << (i*4+j) );
                }
            }
        }

        /* 枚舉所有可能, 0表示全部都不做flip, 65536表示全部都要做flip */
        for (i = 1; i<65536; ++i) {
            ChangedStatus = OriginStatus;
            count = 0;
            TmpIndex = 0;
            for (j = 0; j<16; ++j) {
                if ( ((i>>j) & 0x1 ) == 1) { /* 如果該bit需要做更動 */
                    /* 紀錄row/col */
                    TmpSteps[TmpIndex][0] = (j >> 2) + 1; // row : (j/4) + 1
                    TmpSteps[TmpIndex][1] = (j & 0x3) + 1; // col : (j%4) + 1;
                    ++count;

                    /* 更動整個row */
                    ChangedStatus ^= ( 0xf << ((TmpSteps[TmpIndex][0] - 1) << 2) );
                    /* 更動整個col */
                    ChangedStatus ^= ( 0x1111 << (TmpSteps[TmpIndex][1] - 1) );
                    /* 該bit被更動兩次,因此需要再做一次來還原最後結果 */
                    ChangedStatus ^= (1 << j);
                    ++TmpIndex;
                }
            }

            if (ChangedStatus == 0) {
                if (count<minimun) {
                    Index = TmpIndex;
                    memcpy(Steps, TmpSteps, sizeof(TmpSteps));
                    minimun = count;
                }

            }
        }
        cout << minimun << endl;
        for (i = 0; i<Index; ++i) {
            cout << Steps[i][0] << " " << Steps[i][1] << endl;
        }
    }

    return 0;
}