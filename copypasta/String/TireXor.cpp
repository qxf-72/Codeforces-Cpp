class Tire_Xor
{
	struct TireNode
	{
		TireNode* child[2]{};
		~TireNode(){
			delete child[0];
			delete child[1];
		}
	};
	TireNode* root;
 public:
	Tire_Xor() : root(new TireNode())
	{
	}
	~Tire_Xor()
	{
		delete root;
	}
	void insert(int num)
	{
		TireNode* p = root;
		for (int i = 31; i >= 0; --i)
		{
			int nxt = (num >> i) & 1;
			if (p->child[nxt] == nullptr)
				p->child[nxt] = new TireNode();
			p = p->child[nxt];
		}
	}
	int cal(int num)
	{
		TireNode* p = root;
		int ans = 0;
		for (int i = 31; i >= 0; --i)
		{
			int nxt = ((num >> i) & 1) ? 0 : 1;
			if (p->child[nxt] == nullptr)
				nxt = nxt == 0 ? 1 : 0;
			else
				ans |= (1 << i);
			p = p->child[nxt];
		}
		return ans;
	}
};