//https://leetcode.cn/problems/longest-well-performing-interval/description/
int longestWPI(vector<int> &hours) {
    int n = hours.size();
    for (auto &h: hours)
        h = h > 8 ? 1 : -1;
    vector<int> pre(n + 1);
    partial_sum(hours.begin(), hours.end(), pre.begin() + 1);


    int ans = 0;
    stack<int> st;
    st.push(0);
    for (int i = 1; i <= n; ++i) {
        if (pre[i] < pre[st.top()]) //将可能的左边界入栈
            st.push(i);
    }

    for (int i = n; i > 0; --i) {
        //寻找最长序列
        while (!st.empty() && pre[i] > pre[st.top()]) {
            ans = max(ans, i - st.top());
            st.pop();
        }
    }

    return ans;

}