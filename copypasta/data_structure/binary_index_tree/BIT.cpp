//实现功能:单点更新,区间查询
//以维护区间和为例,维护其他信息仅需要进行少量修改
template<typename T>
class BIT {
private:
    vector<T> data;
    int n;
    int lowbit(int i) {
        return i & -i;
    }

public:
    explicit BIT(vector<T> &arr) {
        n = arr.size();
        data.resize(n + 1);
        // O(n)建树
        for (int i = 1; i <= n; ++i) {
            data[i] += arr[i - 1];
            int j = i + lowbit(i);
            if (j <= n)
                data[j] += data[i];
        }
    }

    T get_sum(int i) {
        T res = 0;
        while (i > 0) {
            res += data[i];
            i -= lowbit(i);
        }
        return res;
    }

    void update(int i, int x) {
        while (i <= n) {
            data[i] += x;
            i += lowbit(i);
        }
    }
};