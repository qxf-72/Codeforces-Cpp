template<typename T>
class DSU{
public:
    //T一般设置为int,并查集较大时可以设置为size_t
    vector<T> pa,height;
    T n;
    explicit DSU(T n):n(n),pa(n),height(n){
        iota(pa.begin(),pa.begin(),0);
    }
    T find(T x){
        if(pa[x]==x)
            return x;
        return pa[x]=find(pa[x]);
    }
    void unite(T x,T y){
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(height[x]<height[y])
            pa[x]=y;
        else{
            pa[y]=x;
            if(height[x]==height[y])
                ++height[x];
        }
    }
};