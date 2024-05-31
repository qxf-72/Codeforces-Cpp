/**
 * @brief 前缀树模板
 *
 */
class Trie {
    struct TrieNode {
        int cnt = 0; // 有多少个字符串以该字符结尾
        TrieNode *children[26]{};
        ~TrieNode() {
            for (int i = 0; i < 26; ++i)
                delete children[i];
        }
    };
    const TrieNode *find(const string &prefix) {
        const TrieNode *p = root;
        for (const char c : prefix) {
            p = p->children[c - 'a'];
            if (p == nullptr) break;
        }
        return p;
    }
    TrieNode *root;

public:
    Trie() :
        root(new TrieNode()) {
    }
    ~Trie() {
        delete root;
    }

    /**
     * @brief 插入字符串
     *
     * @param word
     */
    void insert(const string &word) {
        TrieNode *p = root;
        for (const char c : word) {
            if (p->children[c - 'a'] == nullptr)
                p->children[c - 'a'] = new TrieNode();
            p = p->children[c - 'a'];
        }
        ++p->cnt;
    }

    /**
     * @brief 判断集合中是否存在word
     *
     * @param word
     * @return true
     * @return false
     */
    bool search(const string &word) {
        const TrieNode *p = find(word);
        if (p != nullptr && p->cnt)
            return true;
        return false;
    }

    /**
     * @brief 判断 prefix 是否为 集合中某个字符串 的前缀
     *
     * @param prefix
     * @return true
     * @return false
     */
    bool startsWith(const string &prefix) {
        const TrieNode *p = find(prefix);
        if (p != nullptr)
            return true;
        return false;
    }

    /**
     * @brief 统计 集合中有多少个字符串 是 str的前缀
     *
     * @param str
     * @return int
     */
    int prefixCounter(const string &str) {
        int counter = 0;
        const TrieNode *p = root;
        for (const char c : str) {
            p = p->children[c - 'a'];
            if (p == nullptr) break;
            counter += p->cnt;
        }
        return counter;
    }
};