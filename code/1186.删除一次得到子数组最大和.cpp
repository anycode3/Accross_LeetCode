/*
 * @lc app=leetcode.cn id=1186 lang=cpp
 *
 * [1186] 删除一次得到子数组最大和
 */
#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution
{
public:
    int maximumSum(vector<int> &arr)
    {
        if (arr.empty())
            return 0;
        vector<int> sum(arr.size());    //以第i项为结尾元素的子数组中，求和，和的最大值。
        vector<int> sumdel(arr.size()); //在前i项的子数组中，对任意一个子数组，去掉任意一项后，对其进行求和，取这些和的最大值
        int res = arr[0];               //返回值
        sum[0] = arr[0];
        sumdel[0] = arr[0];
        for (int i = 1; i < arr.size(); ++i)
        {
            sum[i] = max(sum[i - 1] + arr[i], arr[i]);
            sumdel[i] = max(max(sumdel[i - 1] + arr[i], sum[i - 1]), arr[i]);
            res = max(max(sum[i], sumdel[i]), res);
        }
        return res;
    }
};

// int main()
// {
//     Solution t;
//     vector<int> arr = {1, -4, -5, -2, 5, 0, -1, 2};
//     cout << t.maximumSum(arr) << endl;
//     return 0;
// }

// @lc code=end
