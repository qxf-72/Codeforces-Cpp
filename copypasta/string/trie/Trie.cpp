#include <string>
#include <vector>
#include <memory>

using namespace std;

class Trie {
public:
    Trie() : root_(new TireNode()) {}

    //在前缀树中插入字符串，通常在建立前缀树时使用
    void insert(const string& word) {
        TireNode *p = root_.get();
        for (const char c: word) {
            if (p->children[c - 'a'] == nullptr)
                p->children[c - 'a'] = new TireNode();
            p = p->children[c - 'a'];
        }
        p->is_word = true;
        //++p->cnt;
    }

    //组成前缀数的字符集合中是否有word
    bool search(const string& word) {
        const TireNode *p = find(word);
        if (p != nullptr && p->is_word)
            return true;
        return false;
    }

    //是否有字符串以prefix为前缀
    bool startsWith(const string& prefix) {
        const TireNode *p = find(prefix);
        if (p != nullptr)
            return true;
        return false;
    }

private:
    struct TireNode {
        TireNode() : is_word(false) {}

        bool is_word;               //判断是否有单词以该字母为结尾
        //int cnt=0;
        TireNode *children[26]{};   //指向下一个字母
    };

    //在前缀树中查找是否有以prefix为前缀的字符串，并返回对应节点
    const TireNode *find(const string &prefix) {
        const TireNode *p = root_.get();
        for (const char c: prefix) {
            p = p->children[c - 'a'];
            if (p == nullptr) break;
        }
        return p;
    }

    std::unique_ptr<TireNode> root_;
};