/**
 * @brief 异或前缀树模板
 *
 */
class Trie {
    struct Node {
        Node *child[2]{};
        ~Node() {
            delete child[0];
            delete child[1];
        }
    };
    Node *root;

public:
    Trie() :
        root(new Node()) {
    }
    ~Trie() {
        delete root;
    }

    /**
     * @brief 树中插入数字
     *
     * @param num
     */
    void insert(int num) {
        Node *p = root;
        for (int i = 30; i >= 0; --i) {
            int nxt = (num >> i) & 1;
            if (p->child[nxt] == nullptr) {
                p->child[nxt] = new Node();
            }
            p = p->child[nxt];
        }
    }

    /**
     * @brief 计算最大num和树中某个数字的异或值
     *
     * @param num
     * @return int
     */
    int cal(int num) {
        int ans = 0;
        Node *p = root;
        for (int i = 30; i >= 0; --i) {
            int nxt = ((num >> i) & 1) ? 0 : 1;
            if (p->child[nxt] == nullptr) {
                nxt ^= 1;
            } else {
                ans |= (1 << i);
            }
            p = p->child[nxt];
        }
        return ans;
    }
};