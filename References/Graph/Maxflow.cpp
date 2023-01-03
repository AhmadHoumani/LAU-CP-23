#include<bits/stdc++.h>
using namespace std;
#define MAXE 100000
#define MAXN 100000
struct EDGES{
    int u,v,cap,flow,nextedge;
};
class MAXIMUM_FLOW{
    public :
    EDGES edge[MAXE];
    int n , m , level[MAXN],Prev[MAXN],last[MAXN];
    queue<int>Q;
    void init(int N){
        n = N;
        m = -1;
        for(int j=0;j<=n;j++) last[j] = -1;
    }
    void addedge(int a,int b,int c){
        edge[++m].u=a , edge[m].v=b , edge[m].cap=c , edge[m].flow=0 , edge[m].nextedge=last[a] , last[a]=m;
        edge[++m].u=b , edge[m].v=a , edge[m].cap=0 , edge[m].flow=0 , edge[m].nextedge=last[b] , last[b]=m;
    }
    bool level_graph(int src,int snk){
        for(int j=0;j<=n;j++) level[j]=-1;
        int node,nxt;
        level[src]=1;
        Q.push(src);
        while(!Q.empty()){
            node=Q.front(); Q.pop();
            for(int j=last[node];j!=-1;j=edge[j].nextedge){
                nxt=edge[j].v;
                if(level[nxt]==-1 && edge[j].flow<edge[j].cap){
                    level[nxt]=level[node]+1;
                    Q.push(nxt);
                }
            }
        }
        return (level[snk]!=-1);
    }
    int dfs(int node,int snk,int flow){
        int nxt,curflow;
        if(node==snk) return flow;
        for(int &j=Prev[node];j!=-1;j=edge[j].nextedge){
            nxt=edge[j].v;
            if(level[nxt]==level[node]+1 && edge[j].flow<edge[j].cap){
                curflow=dfs(nxt,snk,min(flow,edge[j].cap-edge[j].flow));
                if(curflow==0) continue;
                edge[j].flow+=curflow;
                edge[j^1].flow-=curflow;
                return curflow;
            }
        }
        return 0;
    }
    int MAX_FLOW(int src,int snk){
        int flow,ans=0;
        while(level_graph(src,snk)){
            for(int j=0;j<=n;j++)
                Prev[j]=last[j];
            while(flow=dfs(src,snk,(1<<31)-1)) ans+=flow;
        }
        return ans;
    }
};
