#include <bits/stdc++.h>
#define P(x,y) make_pair(x,y)
using namespace std;
const int MX=(1<<20);
class TwoSAT{
    public :
    int n , timer , cnt;
    vector < vector < int > > v ;
    vector < vector < int > > adj;
    vector < int > low , vi , comp , depth ;
    stack < int > S;
    void Fix(vector < int > &vec , int V){
        vec.resize(n*2);
        fill(vec.begin() , vec.end() , V);
    }
    void init(int N){
        n = N; timer=0; cnt=-1;
        v.clear(); v.resize(n*2); for(int j=0;j<n*2;j++) v[j].clear();
        adj.clear(); adj.resize(n*2); for(int j=0;j<n*2;j++) adj[j].clear();
        Fix(depth , -1);
        Fix(comp , 0);
        Fix(low , 0);
        Fix(vi , 0);
    }
    void imply(int a , int na , int b , int nb){
        a--; b--;
        a*=2; b*=2;
        a+=na; b+=nb;
        v[a].push_back(b);
        v[b^1].push_back(a^1);
    }
    void addor(int a , int na ,  int b , int nb){
        imply(a , na^1 , b , nb);
    }
    void addxor(int a , int na , int b , int nb){
        compadd(a , na , b , nb^1 , a , na^1 , b , nb);
    }
    void compadd(int a , int na , int b , int nb , int c , int nc , int d , int nd){
        addor(a , na , c , nc);
        addor(a , na , d , nd);
        addor(b , nb , c , nc);
        addor(b , nb , d , nd);
    }
    void dfs(int x){
        depth[x] = low[x] = ++timer; vi[x] = 1; S.push(x);
        for(auto nxt : v[x]){
            if(depth[nxt] == -1){
                dfs(nxt);
                low[x] = min(low[x] , low[nxt]);
            }
            else if(vi[nxt]) low[x] = min(low[x] , depth[nxt]);
        }
        if(depth[x] != low[x]) return;
        ++cnt;
        while(1){
            int node = S.top(); S.pop();
            comp[node] = cnt; vi[node] = 0;
            if(node == x) break;
        }
    }
    bool Satisfable(){
        for(int j=0;j<n*2;j++)
            if(depth[j] == -1)
                dfs(j);
        for(int j=0;j<n;j++)
            if(comp[j] == comp[j^1])
                return false;
        return true;
    }
    void build_graph(){
        fill(vi.begin() , vi.end() , 0);
        for(int x=0;x<n*2;x++)
            for(auto nxt : v[x])
                if(comp[x] != comp[nxt])
                    adj[comp[x]].push_back(comp[nxt]);
        for(int x=0;x<=cnt;x++)
            for(auto nxt : adj[x])
                vi[nxt]++;
    }
    void Topo(){
        queue < int > Q;
        for(int j=0;j<=cnt;j++)
            if(vi[j] == 0)
                Q.push(j);
        fill(depth.begin() , depth.end() , 0);
        timer=0;
        while(!Q.empty()){
            int x = Q.front(); Q.pop();
            depth[x] = ++timer;
            for(auto nxt : adj[x]){
                vi[nxt] -- ;
                if(vi[nxt] == 0) Q.push(nxt);
            }
        }
    }
    void solution(vector < int > &sol){
        build_graph();
        Topo();
        sol.resize(n);
        for(int j=0;j<n*2;j+=2){
            if(depth[comp[j]] < depth[comp[j^1]])
                sol[j/2] = 0;
            else sol[j/2] =1;
        }
    }
}G;
