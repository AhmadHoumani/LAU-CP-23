// depth should be cleared with 0 everytest
// timer should be cleared
#include<bits/stdc++.h>
using namespace std;
const int MX=100005;
vector < int > v[MX];
int timer , low[MX] , depth[MX];
vector < int > cutpoints;
vector < pair < int , int > > bridges;
void dfs(int x , int p){
    int cc = 0;
    depth[x] = low[x] = ++timer;
    for(auto nxt : v[x]){
        if(nxt == p) continue;
        if(depth[nxt] == 0) {
            ++cc;
            dfs(nxt , x);
            low[x] = min(low[x] , low[nxt]);
        }
        else low[x] = min(low[x] , depth[nxt]);
        if(low[nxt] > depth[x]) bridges.push_back({x , nxt});
        if(low[nxt] >= depth[x] && p!=-1) cutpoints.push_back(x);
    }
    if(p == -1 && cc>1) cutpoints.push_back(x);
}
int main(){
    dfs(1 , -1);
}

