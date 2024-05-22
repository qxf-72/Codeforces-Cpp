const int N = 200007;
int tree[N + 1]{};
inline int lowbit(int x)
{
	return x & -x;
}

void add(int x, int d)
{
	for (; x <= N; x += lowbit(x))
		tree[x] += d;
}

int ask(int x)
{
	int res = 0;
	for (; x; x -= lowbit(x))
		res += tree[x];
	return res;
}
