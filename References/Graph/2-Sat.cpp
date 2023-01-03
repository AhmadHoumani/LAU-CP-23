#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int>adj[205];
bool vis[205];
vector<int>v;
bool dfs(int x)
{
    if(vis[x^1])return 0;
    vis[x]=1;
    v.push_back(x);
    for(int i=0;i<adj[x].size();++i){
        if(vis[adj[x][i]])continue;
        if(!dfs(adj[x][i]))return 0;
    }
    return 1;
}
void dfs1(){
    for(auto x:v){
        vis[x]=0;
    }
    v.clear();
}
int main()
{
    cin>>n>>m;
    int a,b,c;
    for(int i=0;i<m;++i){
        cin>>a>>b>>c;
    }
    memset(vis,0,sizeof vis);
    bool ok=1;
    for(int i=2;i<=2*n+1;i+=2){
        if(!vis[i]&&!vis[i^1]){
            if(dfs(i)){v.clear();continue;}
            dfs1();
            if(!dfs(i+1)){cout<<"Impossible\n";return 0;}
            v.clear();
        }
    }
    vector<int>sol;
    for(int i=2;i<=2*n;i+=2)if(vis[i])sol.push_back(i/2);
    cout<<sol.size()<<endl;
    for(int i=0;i<sol.size();++i)cout<<sol[i]<<" ";
}
