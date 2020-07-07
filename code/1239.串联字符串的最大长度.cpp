/*
 * @lc app=leetcode.cn id=1239 lang=cpp
 *
 * [1239] 串联字符串的最大长度
 */
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
// @lc code=start
class Solution
{
public:
    // static bool string_length_descend_cmp(const string &a, const string &b)
    // {
    //     return a.size() > b.size();
    // }
    int pos_dup_str_flag = 26; //标记单个字符串内部就已经存在重复字符的位的下标
    int maxLength(vector<string> &arr)
    {
        if (arr.empty())
            return 0;
        // sort(arr.begin(), arr.end(), string_length_descend_cmp);
        vector<unsigned> arr_bit_map(arr.size(), 0); //字符串的bitmap，以asc码进行编码
        int ans = 0;                                 //返回的结果
        for (int i = 0; i < arr.size(); ++i)         //遍历所有字符串，根据字符，将bitmap的相应位置置1
        {
            // int pos_dup_str_flag = 26;
            for (int j = 0; j < arr[i].size(); ++j)
            {
                int pos_encode = arr[i][j] - 'a';              //key
                arr_bit_map[i] ^= (1 << pos_encode);           //异或运算，防止重复字符
                if ((arr_bit_map[i] & (1 << pos_encode)) == 0) //判断单个字符串中是否存在重复的情况
                {
                    arr_bit_map[i] |= (1 << pos_dup_str_flag); //标记
                    break;
                }
            }
        }
        ans = back_trace(arr, arr_bit_map, 0, 0); //回溯，枚举所有可能
        return ans;
    }
    /*
    ** arr
    ** arr_bit_map
    ** i:当前并入的字符串
    ** and_opr_res:目前并入字符串的bitmap进行与运算结果
        */
    int back_trace(const vector<string> &arr, const vector<unsigned> &arr_bit_map,
                   int i, unsigned and_opr_res)
    {
        if (i == arr.size()) //边界
            return 0;
        unsigned before_and_opr_res = and_opr_res;
        if ((arr_bit_map[i] & (1 << pos_dup_str_flag)) || (and_opr_res & arr_bit_map[i])) //当前字符串本身就存在重复字符 或者 当前字符串与已并入的字符串有重复的字符
            return back_trace(arr, arr_bit_map, i + 1, before_and_opr_res);               //不并
        and_opr_res |= arr_bit_map[i];                                                    //并入后与相应的bitmap与运算的结果
        return max(int(arr[i].size()) + back_trace(arr, arr_bit_map, i + 1, and_opr_res),
                   back_trace(arr, arr_bit_map, i + 1, before_and_opr_res)); //取最大值
    }
};

// int main()
// {
//     Solution s;
//     vector<string> arr = {"dasdasda", "asfgfd", "dfasfasfasfasfasf"};
//     s.maxLength(arr);
// }
// @lc code=end
