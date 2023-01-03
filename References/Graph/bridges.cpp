#include<bits/stdc++.h>
using namespace std;
int timer=0;
vector<int>v[1<<17];
int low[1<<17]={0},depth[1<<17]={0};
void dfs(int x , int p){
    low[x]=depth[x]=++timer; int sz_=v[x].size() , nxt , C;
    for(int j=0;j<sz_;j++){
        nxt=v[x][j]; if(nxt==p) continue;
        if(depth[nxt]==-1){
            dfs(nxt , x);
            low[x]=min(low[x] , low[nxt]);
            if(low[nxt] > depth[x]); // bridge :))
        }
        else low[x]=min(low[x] ,depth[nxt]);
    }
}
