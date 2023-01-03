#include<bits/stdc++.h>
using namespace std;
set<int>adj[400005],s;
char ans[400005];
bool vis[400005];
vector<int>v;
int fr[400005],to[400005],n;
int dfs(int x,int ind){
    adj[x].erase(ind);
    if(vis[x]){
        return x;
    }
    vis[x]=1;
    while(!adj[x].empty()){
        ind=*adj[x].begin();adj[x].erase(adj[x].begin());
        int nxt=fr[ind];
        if(nxt==x)nxt=to[ind];
        v.push_back(ind);
        int y=dfs(nxt,ind);
        if(y==-1){v.pop_back();continue;}
        if(y!=x){vis[x]=0;return y;}
        bool p=0;
        while(v.back()!=ind){
            ans[v.back()]="rb"[p];
            p=!p;
            v.pop_back();
        }
        while(!p);
        ans[ind]="rb"[p];
        v.pop_back();
    }
    vis[x]=0;
    s.erase(x);
    return -1;
}
int cnt[400005];
int main()
{
    cin>>n;
    int u,v;
    for(int i=0;i<n;++i){
        scanf("%d%d",&u,&v);
        adj[u].insert(i);
        adj[v].insert(i);
        //s contains all nodes
        s.insert(u);s.insert(v);
        fr[i]=u;to[i]=v;
    }
    while(!s.empty()){
        int x=*s.begin();
        dfs(x,-1);
    }
}
