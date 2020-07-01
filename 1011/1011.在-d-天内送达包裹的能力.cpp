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
    void binary_partition(int left, int right, int &result, int &targetDay, vector<int> &weights, vector<int> &currentWeights)
    {
        int carriage = (left + right) / 2;
        int day = 0;
        int currentLoadWeights = 0;
        for (int i = 0; i < weights.size(); ++i)
        {
            if (currentWeights[i] - currentLoadWeights > carriage)
            {
                day++;
                currentLoadWeights = currentWeights[i - 1];
            }
        }
        if (currentLoadWeights <= *(currentWeights.end() - 1) ||
            currentLoadWeights <= carriage)
            day++;
        if (day > targetDay) //花的天数多了，需要更大的carriage
            left = carriage + 1;
        else //包括与目标天数相等的情况，相等时，要求的carrige一定在包括当前carriage在内往左
            right = carriage;
        if (left != right)
            binary_partition(left, right, result, targetDay, weights, currentWeights);
        else
            result = left = right;
    }

    int shipWithinDays(vector<int> &weights, int D)
    {
        if (weights.empty())
            return 0;
        int minCarriage = *max_element(weights.begin(), weights.end());
        int maxCarriage = accumulate(weights.begin(), weights.end(), 0);
        vector<int> currentWeights(weights.size());
        currentWeights[0] = weights[0];
        for (int i = 1; i < weights.size(); ++i)
            currentWeights[i] += currentWeights[i - 1] + weights[i];
        int result = 0;
        binary_partition(minCarriage, maxCarriage, result, D, weights, currentWeights);
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
