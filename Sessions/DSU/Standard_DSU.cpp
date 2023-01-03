#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

struct dsu {

    int parent[N], size[N], cnt;

    void init(int n) {
        iota(parent, parent + N, 0);
        fill(size, size + n, 1);
        cnt = N;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        cnt--;
        return true;
    }
 } dsu;

int main() {
    int n , u , v;
    cin >> n;
    dsu.init(n);
    while(1){
        int type ;
        cin >> type;
        if(type == 1) {
            cin >> u >> v;
            cout << (int)dsu.merge(u , v); // Merge
        }
        else{
            cin >> u ;
            cout << dsu.find(u); //Find
        }
    }
}

