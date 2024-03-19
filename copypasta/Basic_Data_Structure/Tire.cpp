class Trie
{
	struct TireNode
	{
		TireNode() : is_word(false)
		{
		}
		bool is_word;
		int cnt = 0;
		TireNode* children[26]{};
	};
	const TireNode* find(const string& prefix)
	{
		const TireNode* p = root_.get();
		for (const char c : prefix)
		{
			p = p->children[c - 'a'];
			if (p == nullptr) break;
		}
		return p;
	}
	std::unique_ptr<TireNode> root_;

 public:
	Trie() : root_(new TireNode())
	{
	}

	// 插入字符串，通常在建立前缀树时使用
	void insert(const string& word)
	{
		TireNode* p = root_.get();
		for (const char c : word)
		{
			if (p->children[c - 'a'] == nullptr)
				p->children[c - 'a'] = new TireNode();
			p = p->children[c - 'a'];
		}
		p->is_word = true;
		++p->cnt;
	}

	// 字符集合中是否有word
	bool search(const string& word)
	{
		const TireNode* p = find(word);
		if (p != nullptr && p->is_word)
			return true;
		return false;
	}

	// prefix是否为集合中某个字符串的前缀
	bool startsWith(const string& prefix)
	{
		const TireNode* p = find(prefix);
		if (p != nullptr)
			return true;
		return false;
	}

	// 集合中有多少个字符串是str的前缀
	int prefixCounter(const string& str)
	{
		int counter = 0;
		const TireNode* p = root_.get();
		for (const char c : str)
		{
			p = p->children[c - 'a'];
			if (p == nullptr) break;
			counter += p->cnt;
		}
		return counter;
	}
};