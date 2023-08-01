void Monotonic_Stack(vector<int> &nums) {
    int n = nums.size();
    int nxt[n]; //该元素之后第一个比他小的元素下标
    int pre[n]; //该元素之前第一个比他小的元素下标
    //接下来两行进行预处理
    for (int i = 0; i < n; ++i) nxt[i] = n;
    memset(pre, -1, sizeof(pre));

    stack<int> st1;
    for (int i = 0; i < n; ++i) {
        while (!st1.empty() && nums[i] < nums[st1.top()]) {
            nxt[st1.top()] = i;
            st1.pop();
        }
        st1.push(i);
    }
    stack<int> st2;
    for (int i = n - 1; i >= 0; --i) {
        while (!st2.empty() && nums[i] < nums[st2.top()]) {
            pre[st2.top()] = i;
            st2.pop();
        }
        st2.push(i);
    }
    
    //可以根据得到的边界,根据题目进行一下一步处理
};