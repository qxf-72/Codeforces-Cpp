/*
    实际运用时发现：实际运用时并不需要那么多种操作，而是对于效率的要求很高，BigIntTiny类在实际运用过程中效率偏低，会TLE。
*/
/*

    code from https://github.com/Baobaobear/MiniBigInteger/blob/main/bigint_tiny.h
    代码来源：https://github.com/Baobaobear/MiniBigInteger/blob/main/bigint_tiny.h，本人仅在原有代码基础上修改些许bug,并增加注释

*/
 

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

struct BigIntTiny
{
    int sign{};         // 标志数字的符号
    std::vector<int> v; // 数字部分

    BigIntTiny() : sign(1) {}

    //操作符=已经被重载，会将字符串转换为存储数字的vector
    BigIntTiny(const std::string &s){
        *this = s;
    }
    BigIntTiny(int v){
        char buf[21];
        sprintf(buf, "%d", v);
        *this = buf;            //操作符=被重载，这里采用了和上一个函数类似的方法
    }

    //进行压位操作
    void zip(int unzip){
        //进行压位操作，将4位压为1位进行存储
        if (unzip == 0){
            for (int i = 0; i < (int)v.size(); i++)
                v[i] = get_pos(i * 4) + get_pos(i * 4 + 1) * 10 + get_pos(i * 4 + 2) * 100 + get_pos(i * 4 + 3) * 1000;
        }
        //进行解压操作
        else{
            for (int i = (v.resize(v.size() * 4), (int)v.size() - 1), a; i >= 0; i--)
                a = (i % 4 >= 2) ? v[i / 4] / 100 : v[i / 4] % 100, v[i] = (i & 1) ? a / 10 : a % 10;
        }
        setsign(1, 1);
    }

    //避免越界
    int get_pos(unsigned pos) const { 
        return pos >= v.size() ? 0 : v[pos]; 
    }


    BigIntTiny &setsign(int newsign, int rev){
        //去除前导0
        for (int i = (int)v.size() - 1; i > 0 && v[i] == 0; i--)
            v.erase(v.begin() + i);
        sign = (v.size() == 0 || (v.size() == 1 && v[0] == 0)) ? 1 : (rev ? newsign * sign : newsign);
        return *this;
    }


    std::string to_str() const{
        BigIntTiny b = *this;
        std::string s;
        for (int i = (b.zip(1), 0); i < (int)b.v.size(); ++i)
            s += char(*(b.v.rbegin() + i) + '0');
        return (sign < 0 ? "-" : "") + (s.empty() ? std::string("0") : s);
    }


    bool absless(const BigIntTiny &b) const{
        if (v.size() != b.v.size())
            return v.size() < b.v.size();
        for (int i = (int)v.size() - 1; i >= 0; i--)
            if (v[i] != b.v[i])
                return v[i] < b.v[i];
        return false;
    }

    //取反运算符
    BigIntTiny operator-() const{
        BigIntTiny c = *this;
        c.sign = (v.size() > 1 || v[0]) ? -c.sign : 1;
        return c;
    }

    //操作符=进行重载，这里需要注意数字存储方式是从低位到高位进行存储
    //最终vector中前面存储的是低位，后面存储的是高位
    BigIntTiny &operator=(const std::string &s){
        if (s[0] == '-')
            *this = s.substr(1);
        else{
            for (int i = (v.clear(), 0); i < (int)s.size(); ++i)
                v.push_back(*(s.rbegin() + i) - '0');
            zip(0);
        }
        return setsign(s[0] == '-' ? -1 : 1, sign = 1);
    }


    bool operator<(const BigIntTiny &b) const{
        return sign != b.sign ? sign < b.sign : (sign == 1 ? absless(b) : b.absless(*this));
    }

    bool operator==(const BigIntTiny &b) const { 
        return v == b.v && sign == b.sign; 
    }


    BigIntTiny &operator+=(const BigIntTiny &b){
        if (sign != b.sign)
            return *this = (*this) - -b;
        v.resize(std::max(v.size(), b.v.size()) + 1);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++){
            carry += v[i] + b.get_pos(i);
            v[i] = carry % 10000, carry /= 10000;
        }
        return setsign(sign, 0);
    }


    BigIntTiny operator+(const BigIntTiny &b) const{
        BigIntTiny c = *this;
        return c += b;
    }


    void add_mul(const BigIntTiny &b, int mul){
        v.resize(std::max(v.size(), b.v.size()) + 2);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++){
            carry += v[i] + b.get_pos(i) * mul;
            v[i] = carry % 10000, carry /= 10000;
        }
    }


    BigIntTiny operator-(const BigIntTiny &b) const{
        if (b.v.empty() || b.v.size() == 1 && b.v[0] == 0)
            return *this;
        if (sign != b.sign)
            return (*this) + -b;
        //确保是大减小
        if (absless(b))
            return -(b - *this);
        BigIntTiny c;
        for (int i = 0, borrow = 0; i < (int)v.size(); i++){
            borrow += v[i] - b.get_pos(i);
            c.v.push_back(borrow);
            //根据(32位)补码的移位规则，负数右移31位之后得到-1，正数右移31位得到0
            c.v.back() -= 10000 * (borrow >>= 31);
        }
        return c.setsign(sign, 0);
    }


    BigIntTiny operator*(const BigIntTiny &b) const{
        if (b < *this)
            return b * *this;
        //确保是d大于等于*this
        BigIntTiny c, d = b;
        for (int i = 0; i < (int)v.size(); i++, d.v.insert(d.v.begin(), 0))
            c.add_mul(d, v[i]);
        return c.setsign(sign * b.sign, 0);
    }


    void operator*=(const int &b) {
        for(int i=0;i<v.size();++i)
            v[i]*=b;
        for(int i=0;i<v.size()-1;++i){
            v[i+1]+=v[i]/10000;
            v[i]%=10000;
        }
        if(v.back()>=10000){
            int tmp=v.back()/10000;
            v.back()%=10000;
            v.push_back(tmp);
        }
    }


    BigIntTiny operator/(const BigIntTiny &b) const{
        BigIntTiny c, d;
        BigIntTiny e = b;
        e.sign = 1;

        d.v.resize(v.size());
        double db = 1.0 / (b.v.back() + (b.get_pos((unsigned)b.v.size() - 2) / 1e4) +
                           (b.get_pos((unsigned)b.v.size() - 3) + 1) / 1e8);
        for (int i = (int)v.size() - 1; i >= 0; i--)
        {
            c.v.insert(c.v.begin(), v[i]);
            int m = (int)((c.get_pos((int)e.v.size()) * 10000 + c.get_pos((int)e.v.size() - 1)) * db);
            c = c - e * m, c.setsign(c.sign, 0), d.v[i] += m;
            while (!(c < e))
                c = c - e, d.v[i] += 1;
        }
        return d.setsign(sign * b.sign, 0);
    }


    BigIntTiny operator/(const int &b) {
        std::vector<int> res;
        int rest=0;
        for(int i=v.size()-1;i>=0;--i){
            rest=rest*10000+v[i];
            res.push_back(rest/b);
            rest%=b;
        }
        int i=0;
        while(i<res.size()&&res[i]==0) ++i;
        res.erase(res.begin(),res.begin()+i);
        std::reverse(res.begin(),res.end());
        BigIntTiny ans;
        ans.v=std::move(res);

        return ans;
    }


    BigIntTiny operator%(const BigIntTiny &b) const { return *this - *this / b * b; }
    bool operator>(const BigIntTiny &b) const { return b < *this; }
    bool operator<=(const BigIntTiny &b) const { return !(b < *this); }
    bool operator>=(const BigIntTiny &b) const { return !(*this < b); }
    bool operator!=(const BigIntTiny &b) const { return !(*this == b); }
};
