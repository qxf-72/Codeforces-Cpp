void Monotonic_Stack(vector<int>& nums)
{
	int n = nums.size();
	vector<int> nxt(n, n);    //该元素之后第一个比他小的元素下标
	vector<int> pre(n, -1);    //该元素之前第一个比他小的元素下标

	stack<int> st1;
	for (int i = 0; i < n; ++i)
	{
		while (!st1.empty() && nums[i] < nums[st1.top()])
		{
			nxt[st1.top()] = i;
			st1.pop();
		}
		st1.push(i);
	}
	stack<int> st2;
	for (int i = n - 1; i >= 0; --i)
	{
		while (!st2.empty() && nums[i] < nums[st2.top()])
		{
			pre[st2.top()] = i;
			st2.pop();
		}
		st2.push(i);
	}
};