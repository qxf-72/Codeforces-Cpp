#include <string>
#include <vector>
#include <memory>

using namespace std;

//线段树模板，根据不同要求进行修改使用,可以进行的操作如下：
//区间求和，区间最大值，区间最小值
class SegmentTree{
private:
    static const int INF=0x3f3f3f3f;
    vector<int> dat;
public:
    int n;
    void init(int n_){
        //n_为元素数量，但是为了便于处理，将其元素个数扩大到2的幂
        n=1;
        while(n<n_) n*=2;
        dat.resize(2*n-1);

        //不同要求，数组初始化也不同：
        //区间求和 0 ；区间最小值 INF； 区间最大值：—INF
        for(int i=0;i<2*n-1;++i) dat[i]=0;
    }

    //把下标为k(从0开始)的值进行更新
    void update(int k,int a){
        k+=n-1;
        dat[k]=a;
        while(k>0){
            k=(k-1)/2;
            //不同要求，数组更新也不同：
            //区间求和   :   dat[k]=dat[2*k+1]+dat[2*k+2];
            //区间最小值 :   dat[k]=min(dat[2*k+1],dat[2*k+2]);
            //区间最大值 :   dat[k]=max(dat[2*k+1],dat[2*k+2]);
            dat[k]=dat[2*k+1]+dat[2*k+2];
        }
    }

    //查询区间[a,b)的最小值
    //k为当前区间对应的节点的下标,初始设为0
    //[l,r)为当前区间，初始为[0,n)
    int query(int a,int b,int k,int l,int r){
        //区间求和   :   return 0;
        //区间最小值 :   return INF;
        //区间最大值 :   return -INF;
        if(r<=a || b<=l) return 0;
        if(a<=l && b>=r) return dat[k];
        else{
            int v_l=query(a,b,k*2+1,l,(l+r)/2);
            int v_r=query(a,b,k*2+2,(l+r)/2,r);
            //区间求和   :   return v_l+v_r;
            //区间最小值 :   return min(v_l,v_r);
            //区间最大值 :   return max(v_l,v_r);
            return v_l+v_r;
        }
    }
};