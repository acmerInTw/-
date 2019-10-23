/*    Flip Game
 *    URL : http://poj.org/problem?id=1753
 *
 *    1. 將input轉成0/1然後儲存在一個int裡面,每一個bit代表每一個輸入的狀態
 *       例如: bwwb                 0110                              0  1  2  3
 *             bbwb   轉成0/1 ===>  0010   對應到int每個位元位置  ===> 4  5  6  7
 *             bwwb                 0110                             8  9  10 11
 *             bwww                 0111                            12  13 14 15  
 *
 *    2. 一共有16個,因此共有2^16種可能
 *       因為所有枚舉不多,因為用枚舉方法來解
 *    3. 當i的bit為1,表示該位置需要做flip,因此上下左右也都要做flip
 *    4. 當每個i檢查完時,看看ChangeStatus的值是全部bit為0或是全為1
 *
 */

#include <iostream>
using namespace std;

#define NUMS 10

int main()
{
    int i, j;
    char input[4][5];
    int OriginStatus;
    int ChangedStatus;
    int minimum;
    int count;

    while (cin >> input[0] >> input[1] >> input[2] >> input[3]) {
        OriginStatus = 0;
        minimum = 17;
        
        /* 將input儲存在int裡 */
        for (i = 0; i<4; ++i) {
            for (j = 0; j < 4; ++j) {
                if (input[i][j] == 'w') {
                    OriginStatus |= ( 1 << (i*4 + j) );
                }
            }
        }

        /* 枚舉所有可能, 0表示全部都不做flip, 65536表示全部都要做flip */
        for (i = 0; i<65536; ++i) {
            count = 0;
            ChangedStatus = OriginStatus;
            for (j = 0; j<16; ++j) {
                if ( (i>>j) & 0x1 == 1 ) { /* 如果該bit需要做flip */
                    ++count;
                    ChangedStatus ^= (1 << j);
                    if (j>3) { /* flip上面部分 */
                        ChangedStatus ^= (1 << (j-4));
                    }
                    if (j<12) { /* flip 下面部分 */
                        ChangedStatus ^= (1 << (j+4));
                    }
                    if (j%4 != 0) { /* flip左邊部分 */
                        ChangedStatus ^= (1 << (j-1));
                    }
                    if (j !=3 && j !=7 && j != 11 && j != 15) { /* flip右邊部分 */
                        ChangedStatus ^= (1 << (j+1));
                    }
                }
            }
            if ( (ChangedStatus == 0 || ChangedStatus == 65535) && (count<minimum)) {
                minimum = count;
            }
        }
        if (minimum == 17)
            cout << "Impossible" << endl;
        else
            cout << minimum << endl;
    }

    return 0;
}