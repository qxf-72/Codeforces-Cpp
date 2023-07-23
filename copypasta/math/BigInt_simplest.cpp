#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>


const int N = 5000;
struct BigInt_simplest {
    int data[N]{};

    BigInt_simplest() { data[0] = 1;}

    explicit BigInt_simplest(int x) {
        data[0] = 1;
        int i = 1;
        while (x) {
            data[i++] = x % 10;
            x /= 10;
        }
        data[0] = --i;
    }

    BigInt_simplest operator*(const int &x) {
        BigInt_simplest a;
        int len;
        a.data[0] = data[0];
        for(int i=1;i<=data[0];++i)
            a.data[i] = data[i] * x;

        for (int i = 1; i <= a.data[0] || a.data[i]; len = ++i) {
            a.data[i + 1] += a.data[i] / 10;
            a.data[i] %= 10;
        }
        a.data[len] ? a.data[0] = len : a.data[0] = --len;
        return a;
    }

    BigInt_simplest operator/(const int &x) {
        BigInt_simplest a;
        a.data[0] = data[0];
        int rest = 0;
        for (int i = data[0]; i >= 1; i--) {
            rest = rest * 10 + data[i];
            a.data[i] = rest / x;
            rest %= x;
        }
        while (!a.data[a.data[0]] && a.data[0] > 1) a.data[0]--;
        return a;
    }

    bool operator<(const BigInt_simplest &x) const {
        if (data[0] == x.data[0]) {
            int i;
            for (i = data[0]; data[i] == x.data[i] && i > 1; i--);
            if (i >= 1) return data[i] < x.data[i];
            else return false;
        } else return data[0] < x.data[0];
    }

    void Print(){
        for(int i=data[0];i>=1;--i)
            std::cout<<data[i];
    }
};