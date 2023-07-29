using namespace std;
class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for(auto& e:edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        int dis[n];

        function<int(int)> bfs=[&](int start)->int{
            memset(dis,-1, sizeof(dis));
            dis[start]=0;
            int ans=INT_MAX;
            queue<pair<int,int>> que;
            que.emplace(start,-1);
            while(!que.empty()){
                auto [cur,fa]=que.front();
                que.pop();
                for(auto next:g[cur]){
                    if(dis[next]==-1){
                        dis[next]=dis[cur]+1;
                        que.emplace(next,cur);
                    }else if(fa!= next)
                        ans=min(ans,dis[cur]+dis[next]+1);
                }
            }
            return ans;
        };

        int ans=INT_MAX;
        for(int i=0;i<n;++i){
            ans=min(ans,bfs(i));
        }
        return ans==INT_MAX?-1:ans;
    }
};