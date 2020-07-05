/*
 * @lc app=leetcode.cn id=1011 lang=cpp
 *
 * [1011] 在 D 天内送达包裹的能力
 */
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;
// @lc code=start
class Solution
{
public:
    void binary_partition(int left, int right, int &result, int &targetDay, vector<int> &currentWeights)
    {
        int carriage = (left + right) / 2;              //当前的轮船负重量，取中间
        int day = 0;                                    //记录当前carriage最小消耗的天数
        int currentLoadWeights = 0;                     //记录已经运走的货物重量
        for (int i = 0; i < currentWeights.size(); ++i) //分配装载
        {
            if (currentWeights[i] - currentLoadWeights > carriage) //加上第i个货物后超出了此趟运载量，那么前面已经装载好的就可以发车了
            {
                day++;                                      //趟数+1，发车
                currentLoadWeights = currentWeights[i - 1]; //已经运走的重量进行累加
            }
        }
        if (currentLoadWeights <= *(currentWeights.end() - 1) ||
            currentLoadWeights <= carriage) //"分配装载"循环中，最后一趟的装载还没有发车
            day++;
        if (day > targetDay) //花的天数多了，需要更大的carriage
            left = carriage + 1;
        else //包括与目标天数相等的情况，相等时，要求的carrige一定在包括当前carriage在内往左
            right = carriage;
        if (left != right) //二分
            binary_partition(left, right, result, targetDay, currentWeights);
        else //结果
            result = left = right;
    }

    int shipWithinDays(vector<int> &weights, int D)
    {
        if (weights.empty())
            return 0;
        int minCarriage = *max_element(weights.begin(), weights.end());  //可能解的左边界
        int maxCarriage = accumulate(weights.begin(), weights.end(), 0); //可能解的右边界
        vector<int> currentWeights(weights.size());                      //weights的累加
        currentWeights[0] = weights[0];
        for (int i = 1; i < weights.size(); ++i)
            currentWeights[i] += currentWeights[i - 1] + weights[i];
        int result = 0;                                                        //存储输出结果
        binary_partition(minCarriage, maxCarriage, result, D, currentWeights); //二分查找
        return result;
    }
};

// int main()
// {
//     Solution t;
//     vector<int> weights = {1,
//                            2,
//                            3,
//                            4,
//                            5,
//                            6,
//                            7,
//                            8,
//                            9,
//                            10};
//     int D = 5;
//     cout << t.shipWithinDays(weights, D) << endl;
//     return 0;
// }
// @lc code=end
