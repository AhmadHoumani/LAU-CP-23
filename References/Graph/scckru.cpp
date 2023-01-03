// SCC using Kosaraju's algorithm


// this code is the solution to probles "G - Hit the Light Switches"
// you can use to solve any other problem...
#include <bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
// graph and it's trandpose:
vector<vector<int> >adj, rdj;
// nodes[x] is a list of nodes that belong to scc x:
vector<vector<int> >nodes;
// the adjList of the result SCC DAG:
vector<set<int> > sccAdj;
// dfs visited:
int v[100005];
// comp[x] is the number of SCC that node x belong to:
int comp[100005];
// ncmp is the total number of scc:
int ncmp, n, m;

stack<int> s;

void dfs( int x ) {
	for( int i = 0; i < adj[x].size(); ++i ) {
		int nx = adj[x][i];
		if( !v[nx] ) {
			v[nx] = 1;
			dfs( nx );
		}
	}
	s.push( x );
}

void rdfs( int x, int cmp ) {
	comp[x] = cmp;
	nodes[cmp].pb( x );

	for( int i = 0; i < rdj[x].size(); ++i ) {
		int nx = rdj[x][i];
		if( !v[nx] ) {
			v[nx] = 1;
			rdfs( nx, cmp );
		} else if( comp[nx] != comp[x] ) {
			sccAdj[comp[x]].insert( comp[nx] );
		}
	}
}

int main() {
	int T;
	scanf( "%d", &T );
	for( int tc = 1; tc <= T; ++tc ) {
		scanf( "%d%d", &n, &m );
		adj.assign( n + 1, vector<int>() );
		rdj.assign( n + 1, vector<int>() );
		sccAdj.clear();
		nodes.clear();
		memset( v, 0, sizeof v );
		ncmp = 0;
		for( int i = 0; i < m; ++i ) {
			int a, b;
			scanf( "%d%d", &a, &b );
			adj[a].pb( b );
			rdj[b].pb( a );
		}
		for( int i = 1; i <= n; ++i ) {
			if( !v[i] ) {
				v[i] = 1;
				dfs( i );
			}
		}
		memset( v, 0, sizeof v );
		while( !s.empty() ) {
			int x = s.top();
			s.pop();
			if( !v[x] ) {
//			printf( "component #%d:\n", ncmp + 1 );
				sccAdj.push_back( set<int>() );
				nodes.push_back( vector<int>() );
				v[x] = 1;
				rdfs( x, ncmp++ );
			}
		}
		int ans = 0;
		for( int i = 0; i < sccAdj.size(); ++i ) {
			if( sccAdj[i].size() == 0 )
				ans++;
		}
		printf( "Case %d: %d\n", tc, ans );
	}
	return 0;
}
