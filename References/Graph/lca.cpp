#include<bits/stdc++.h>
#define P(x,y) make_pair(x,y)
using namespace std;
const int MX=100009 , MXL=18;
vector < int > v[MX];
int n , QN , depth[MX] , par[MXL][MX] ;
int sum[MX] ;
void Pdfs(int x , int p){
    int nxt , C , sz=v[x].size();
    for(int j=0;j<sz;j++){
        nxt=v[x][j];
        if(nxt == p) continue;
        depth[nxt]=depth[x]+1;
        par[0][nxt]=x;
        Pdfs(nxt , x);
    }
}
void process(){
    for(int j=1;j<MXL;j++)
        for(int i=1;i<=n;i++)
            par[j][i]=par[j-1][par[j-1][i]];
}
int Kth(int x , int K){
    int node=x;
    for(int j=0;j<MXL;j++)
        if((K&(1<<j)))
           node=par[j][node];
    return node;
}
int LCA(int a , int b){
    if(a==b) return a;
    if(depth[a] > depth[b]) swap(a , b);
    b=Kth(b , depth[b]-depth[a]);
    if(a==b) return b;
    for(int j=MXL-1;j>=0;j--)
        if(par[j][a] != par[j][b])
            a=par[j][a] , b=par[j][b];
    return par[0][a];
}
int main(){
   
    depth[1]=1;
    Pdfs(1 , -1);
    process();
    
 
}
