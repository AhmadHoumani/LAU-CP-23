#include <bits/stdc++.h>

using namespace std;
struct node{
	int val;
	static node* empty;
	node * left , * right;
	node(){
		left=right=this;
		val=0;
	}
	node(int v,node * l =empty,node * r=empty){
		val=v;
		left=l;
		right=r;
	}

};
node * node::empty=new node();
const int MAXN=100001;
node * roots [MAXN];

node* insert(node* cur,int val,int ns=-1e9,int ne=1e9){
	if (val<ns||val>ne)return cur;
	if (ns==ne){
		return new node(cur->val+1);
	}
	int mid=ns+(ne-ns)/2;
	node * l=insert(cur->left,val,ns,mid);
	node * r=insert(cur->right,val,mid+1,ne);
	return new node(l->val+r->val,l,r);
}
int query(node * im1,node * j , int k,int ns=-1e9,int ne=1e9){
	if (ns==ne)return ns;
	int cur=j->left->val-im1->left->val;
	int mid=ns+(ne-ns)/2;
	if (cur<k){
		return query(im1->right,j->right,k-cur,mid+1,ne);
	}
	return query(im1->left,j->left,k,ns,mid);
}

int main(){
	roots[0]=node::empty;
	int n,m;
	scanf("%d %d",&n,&m);//	cin>>n>>m;
	for (int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
//		cin>>x;
		roots[i]=insert(roots[i-1],x);
	}
	for (int i=0;i<m;++i){
		int s,e,k;
		scanf("%d %d %d",&s,&e,&k);
//		cin>>s>>e>>k;
		printf("%d\n",query(roots[s-1],roots[e],k));
//		cout<<query(roots[s-1],roots[e],k)<<"\n";
	}

	return 0;
}
