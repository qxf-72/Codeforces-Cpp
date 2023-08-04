//求按位或结果等于 任意给定数字 的子数组的最短长度/最长长度
class Solution {
public:
    vector<int> smallestSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<pair<int, int>> ors; // 按位或的值 + 对应子数组的右端点的最小值
        for (int i = n - 1; i >= 0; --i) {
            ors.emplace_back(0, i);
            ors[0].first |= nums[i];
            int k = 0;
            for (int j = 1; j < ors.size(); ++j) {
                ors[j].first |= nums[i];
                if (ors[k].first == ors[j].first)
                    ors[k].second = ors[j].second; // 合并相同值，下标取最小的
                else ors[++k] = ors[j];
            }
            ors.resize(k + 1);
            
            ans[i] = ors[0].second - i + 1;
        }
        return ans;
    }
};


//求出所有子数组的按位或的结果
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& nums) {
        int n = nums.size();
        vector<int> ors; 
        unordered_set<int> st;
        for (int i = n - 1; i >= 0; --i) {
            ors.emplace_back(0);
            ors[0] |= nums[i];
            int k = 0;
            for (int j = 1; j < ors.size(); ++j) {
                ors[j] |= nums[i];
                if (ors[k] == ors[j])
                    continue; 
                else ors[++k] = ors[j];
            }
            ors.resize(k + 1);
            for(auto num:ors)
                st.insert(num);
        }
        return st.size();
    }
};