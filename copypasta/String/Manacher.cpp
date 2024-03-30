const int MAXN = 110'000;
int dp[MAXN * 2 + 5];	//注意数组大小
char str[MAXN * 2 + 5];
int Manacher(char* s)
{
	int N = 0, len = strlen(s + 1);
	str[0] = '$';
	for (int i = 1; i <= len; ++i)
	{
		str[++N] = '#';
		str[++N] = s[i];
	}
	str[++N] = '#', str[++N] = '^';
	int right = 0, center = 0;
	for (int i = 1; i <= N; ++i)
	{
		if (i < right)
			dp[i] = min(dp[2 * center - i], right - i);
		else
		{
			right = i;
			dp[i] = 1;
		}
		while (str[i - dp[i]] == str[i + dp[i]])
			++dp[i];
		if (i + dp[i] > right)
		{
			right = i + dp[i];
			center = i;
		}
	}

//	vector<int> lps;
//	for (int i = 2; i <= N - 2; i += 2)
//		lps.push_back(dp[i]);

	// 找最长回文长度
	int lps = 0;
	for (int i = 1; i <= N; i++)
		lps = max(lps, dp[i] - 1);
	return lps;
}