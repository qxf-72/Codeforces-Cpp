const int N = 2e5 + 7;
int fa[N], sz[N];

void dsu_init(int n)
{
	for (int i = 0; i < n; ++i)
		fa[i] = i, sz[i] = 1;
}

int find(int x)
{
	if (x == fa[x])
		return x;
	return fa[x] = find(fa[x]);
}

void unite(int x, int y)
{
	x = find(x), y = find(y);
	if (sz[x] > sz[y])
		sz[x] += sz[y], fa[y] = x;
	else
		sz[y] += sz[x], fa[x] = y;

}


int main( int argc, char *argv[] )
{
    
    return 0;
}