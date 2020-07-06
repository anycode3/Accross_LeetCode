/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] 字符串解码
 */
#include <string>
#include <stack>
#include <deque>
using namespace std;
// @lc code=start
class Solution
{
public:
    string decodeString(string s)
    {
        stack<int> dup_times;
        stack<int> dup_start;
        string tmp_dup_times;
        string ans;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] >= 48 && s[i] <= 57)
                tmp_dup_times += s[i];
            else if (s[i] == '[')
            {
                dup_times.push(atoi(tmp_dup_times.c_str()));
                tmp_dup_times.clear();
                dup_start.push(ans.size());
            }
            else if (s[i] == ']')
            {
                string tmp_dup_str = ans.substr(dup_start.top());
                for (int j = 1; j < dup_times.top(); ++j)
                    ans += tmp_dup_str;
                dup_times.pop();
                dup_start.pop();
            }
            else
                ans += s[i];
        }
        return ans;
    }
};
// @lc code=end
