/*
 * @lc app=leetcode.cn id=241 lang=cpp
 *
 * [241] 为运算表达式设计优先级
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// @lc code=start
class Solution
{
public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> res; //返回结果
        for (int i = 0; i < input.size(); ++i)
        {
            if (input[i] == '+' || input[i] == '-' || input[i] == '*')
            {
                auto res1 = diffWaysToCompute(input.substr(0, i));  //前段
                auto res2 = diffWaysToCompute(input.substr(i + 1)); //后段
                for (auto r1 : res1)                                //计算结果
                {
                    for (auto r2 : res2)
                    {
                        if (input[i] == '+')
                            res.push_back(r1 + r2);
                        else if (input[i] == '-')
                            res.push_back(r1 - r2);
                        else if (input[i] == '*')
                            res.push_back(r1 * r2);
                    }
                }
            }
        }
        if (res.empty())
            res.push_back(atoi(input.c_str()));
        return res;
    }
};
// @lc code=end
