#include<bits/stdc++.h>
using namespace std;
const int MAXE = 100000;
const int MAXN = 10000;
const int inf = (1<<29);
struct EDGES{
    int u , v , cap , flow , nextedge , cost;
};
class MCMF{
    int n , m , dis[MAXN] , last[MAXN] , state[MAXN] , P[MAXN];
    EDGES edge[MAXE];
    deque < int > Q;
    public:
    void init(int N){
        n = N;
        m = -1;
        for(int j=0;j<=n;j++) last[j] = -1;
    }
    void addedge(int a , int b , int c , int d){
        edge[++m].u = a ; edge[m].v = b ; edge[m].cap = c ; edge[m].cost = d; edge[m].flow = 0 ; edge[m].nextedge = last[a]; last[a] = m;
        edge[++m].u = b ; edge[m].v = a; edge[m].cap = 0; edge[m].cost = -d; edge[m].flow=0; edge[m].nextedge = last[b]; last[b] = m;
    }
    bool getpath(int src , int snk){
        Q.clear();
        for(int j=0;j<=n;j++){
            state[j] = 0;
            dis[j] = inf;
        }
        Q.push_back(src); dis[src] = 0;
        state[src] = 1;
        while(!Q.empty()){
            int x = Q.front(); Q.pop_front();
            state[x] = 2;
            for(int j = last[x] ; j != -1 ; j = edge[j].nextedge){
                int nxt = edge[j].v;
                if(edge[j].cap - edge[j].flow > 0 && dis[nxt] > dis[x] + edge[j].cost){
                    dis[nxt] = dis[x] + edge[j].cost;
                    P[nxt] = j;
                    if(state[nxt] == 0)
                        Q.push_back(nxt);
                    if(state[nxt] == 2)
                        Q.push_front(nxt);
                    state[nxt] = 1;
                }
            }
       }
       return dis[snk] != inf;
    }
    pair < int , int > augment(int x , int src , int flow){
        if(x == src) return make_pair(flow , 0);
        auto &E = edge[P[x]] , &rev=edge[(P[x]^1)];
        auto tosrc = augment(E.u , src , min(flow , E.cap - E.flow));
        tosrc.second += E.cost;
        E.flow += tosrc.first;
        rev.flow -= tosrc.first;
        return tosrc;
    }
    pair < int , int > MAXFLOW(int src , int snk){
        int flow = 0 , cost = 0;
        while(getpath(src , snk)){
            auto add = augment(snk , src , inf);
            flow += add.first;
            cost += add.second * add.first;
        }
        return make_pair(flow , cost);
    }
}G;
