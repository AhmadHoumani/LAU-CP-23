/// Dijkstra
const int MX=1e5;// Check that shit!! 
int dis[MX];
struct STATE
{
    int node,dis;
        STATE(){
        node=dis=0;
        }
        STATE(int a,int b)
        {
            node =a;
            dis=b;
        }
};
bool operator <(const STATE& x, const STATE& y)
{
    if(x.dis!=y.dis)return x.dis>y.dis;
    return x.node<y.node;
}
void dij(int source)
{
    fill(dist,dist + n+6, INF);
    priority_queue<STATE> pq;
    STATE ini(source,0);
    pq.push(ini);
    dist[source]=0;
    while(!pq.empty())
    {
        int x=pq.top().node;
        pq.pop();
        for(auto u : adj[x])
        {
            if(dist[u.first]>dist[x]+u.second)
            {
                dist[u.first]=dist[x]+u.second;
                pq.push({u.first,dist[u.first]});
            }
        }
    }
}