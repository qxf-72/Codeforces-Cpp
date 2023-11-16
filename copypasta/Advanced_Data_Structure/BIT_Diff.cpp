// 以维护区间和为例,维护其他信息仅需要进行少量修改
template <typename T>
class BIT_Diff
{
private:
    vector<T> data_a; // 维护 差分数组a[i] 的前缀和
    vector<T> data_b; // 维护 i*a[i] 的前缀和
    
    int n;
    int lowbit(int i) { return i & -i; }
    
    void add(vector<T> &arr, int i, T x)
    {
        while (i <= n)
        {
            arr[i] += x;
            i += lowbit(i);
        }
    }
    T sum(vector<T> &arr, int i)
    {
        T res = 0;
        while (i > 0)
        {
            res += arr[i];
            i -= lowbit(i);
        }
        return res;
    }

public:
    explicit BIT_Diff(vector<T> &arr)
    {
        n = arr.size();
        data_a.resize(n + 1);
        data_b.resize(n + 1);
        // O(n)建树
        for (int i = 1; i <= n; ++i)
        {
            // 进行差分
            if (i == 1)
            {
                data_a[i] += arr[i - 1];
                data_b[i] += arr[i - 1] * i;
            }
            else
            {
                data_a[i] += arr[i - 1] - arr[i - 2];
                data_b[i] += (arr[i - 1] - arr[i - 2]) * i;
            }
            int j = i + lowbit(i);
            if (j <= n)
            {
                data_a[j] += data_a[i];
                data_b[j] += data_b[i];
            }
        }
    }
    void range_add(int l, int r, int x)
    {
        add(data_a, l, x);
        add(data_a, r + 1, -x);
        add(data_b, l, l * x);
        add(data_b, r + 1, -(r + 1) * x);
    }
    T query(int l, int r)
    {
        return sum(data_a, r) * (r + 1) - sum(data_b, r) - sum(data_a, l - 1) * l + sum(data_b, l - 1);
    }
};