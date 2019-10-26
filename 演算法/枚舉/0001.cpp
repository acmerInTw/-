/*    Largest Rectangle in a Histogram
 *    URL : http://poj.org/problem?id=2559
 *
 *    Language: C++
 *    *有scanf()就要用C++,不能用G++,不然在POJ上會Compile Error
 *    *在C++上有Runtime Error,但是local卻不會有,可以換成G++試試看
 */

#include <iostream>
#include <cstring>
using namespace std;

#define NUMS 100000
typedef long long LL;

int main()
{
    int n, i;
    int Top;
    LL MaxArea, TmpArea;
    int RecHeight[NUMS];  /* 紀錄輸入的長條圖高度 */
    int StackIndex[NUMS]; /* 向右或向左尋找邊界時,一邊記錄經過的長條圖index*/
    int LeftIndex[NUMS];  /* 紀錄在左邊處小於該長條圖高度的邊界index */
    int RightIndex[NUMS]; /* 紀錄在右邊處小於該長條圖高度的邊界index */

    while (scanf("%d", &n)) {
        if (n == 0)
            break;

        for (i = 0; i < n; ++i)
            scanf("%d", &RecHeight[i]);

        MaxArea = 0;
        Top = -1;
        memset(LeftIndex, -1, sizeof(LeftIndex));
        memset(RightIndex, -1, sizeof(RightIndex));

        /* 向右尋找邊界 */
        for (i = 0; i<n; ++i) {
            while (Top > -1 && RecHeight[StackIndex[Top]] > RecHeight[i]) {
                RightIndex[StackIndex[Top]] = i;
                --Top;
            }
            StackIndex[++Top] = i;
        }

        Top = -1;

        /* 向左尋找邊界 */
        for (i = n-1; i>=0; --i) {
            while (Top > -1 && RecHeight[StackIndex[Top]] > RecHeight[i]) {
                LeftIndex[StackIndex[Top]] = i;
                --Top;
            }
            StackIndex[++Top] = i;
        }

        /* 每個長條圖左右兩邊邊界找到後就可以算出以該長條圖為中心向旁邊擴展的最大長方形 */
        for (i = 0; i<n; ++i) {
            int r = (RightIndex[i] == -1) ? n : RightIndex[i];
            int l = (LeftIndex[i] == -1) ? -1 : LeftIndex[i];
            TmpArea = (r - l - 1) * ( (LL)RecHeight[i]);
            if (TmpArea > MaxArea)
                MaxArea = TmpArea;
        }

        cout << MaxArea << endl;

    }
    return 0;
}