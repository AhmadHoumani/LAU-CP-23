#include <bits/stdc++.h>
typedef long double ld;
typedef long long ll;
using namespace std;
const int MX=1e5+4;
int pa[MX][22],tree[4*MX],cnt[MX],Subs[MX],order[MX],depth[MX],nonorder[MX], n,q,counter=1;;;
vector<int>nigger[MX];
vector<int> Onech;
void Fillsparse()
{
  for(int i=1;i<22;i++)
    {
        for(int j=1;j<=n;j++)
            pa[j][i]=pa[pa[j][i-1]][i-1];
    }
}
int Kth(int x , int K){
    int node=x;
    for(int j=0;j<22;j++)
        if((K&(1<<j)))
           node=pa[node][j];
    return node;
}
int lca(int a , int b){
    if(a==0)return b;
    if(b==0)return a;
    if(a==b) return a;
    if(depth[a] > depth[b]) swap(a , b);
    b=Kth(b , depth[b]-depth[a]);
    if(a==b) return b;
    for(int j=22-1;j>=0;j--)
        if(pa[a][j] != pa[b][j])
            a=pa[a][j] , b=pa[b][j];
    return pa[a][0];
}
int Nde;
void insrt(int x=1,int l=1,int r=counter-1)
{
    if(l>Nde||r<Nde)return;
    if(l==r&&Nde==r)
    {
        tree[x]=nonorder[Nde];
        return;
    }
    int mid=(l+r)/2;
    insrt(2*x,l,mid);
    insrt(2*x+1,mid+1,r);
    tree[x]=lca(tree[2*x],tree[2*x+1]);
}
void delet(int x=1,int l=1,int r=counter-1)
{
    if(l>Nde||r<Nde)return;
    if(l==r&&Nde==r)
    {
        tree[x]=0;
        return;
    }
    int mid=(l+r)/2;
    delet(2*x,l,mid);
    delet(2*x+1,mid+1,r);
    tree[x]=lca(tree[2*x],tree[2*x+1]);
}
int Left[MX],Right[MX];
int search_(int x=1,int l=1,int r=counter-1)
{
   // cout<<Left[Nde]<<' '<<Right[Nde]<<endl;
    if(l>Right[Nde]||r<Left[Nde])return 0;
    if(l>=Left[Nde]&&Right[Nde]>=r)
    {
        return tree[x];
    }
    int mid=(l+r)/2;
    //cout<<search_(2*x,l,mid)<<' '<<search_(2*x+1,mid+1,r)<<endl;
    return lca(search_(2*x,l,mid),search_(2*x+1,mid+1,r));
}
int dfs(int x,int root,int z)
{
    int ans=nigger[x].empty();
    depth[x]=z;
    Subs[x]=root;
    if(ans){
    order[x]=counter++;
    nonorder[counter-1]=x;
    }
    for(auto u : nigger[x])
        {
            if(x==1)
            {
                 Left[u]=counter;
                ans+=dfs(u,u,z+1);
                Right[u]=counter-1;
                //cout<<Right[u]<<' '<<Left[u]<<endl;
                continue;
            }
            ans+=dfs(u,root,z+1);
        }
    cnt[x]=ans;
   // cout<<x<<' '<<Subs[x]<<endl;
    return ans;
}
int shbab[MX];
int main()
{
    freopen("gangsters.in","r",stdin);
    freopen("gangsters.out","w",stdout);


    cin>>n>>q;
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&pa[i][0]);
        nigger[pa[i][0]].push_back(i);
    }
    Fillsparse();
    dfs(1,1,0);
    int ans=0,ans1=0;
    for(int i=0;i<q;i++)
    {
        char c;
        int node;
        scanf(" %c %d",&c,&node);
        if(shbab[Subs[node]])ans1--;
        Nde=Subs[node];
        //cout<<Nde<<' '<<node<<' ';
       // return 0;
        int vv=search_();
        ans-=cnt[vv]-shbab[Subs[node]];
       // return 0;
        if(c=='+')
        {
            shbab[Subs[node]]++;
            Nde=order[node];

            insrt();
            Nde=Subs[node];;
        int v=search_();
//        cout<<Left[Nde]<<' '<<Right[Nde]<<endl;
       // cout<<"the lca is "<<v<<endl;
            ans+=cnt[v]-shbab[Subs[node]];
        }
        if(c=='-')
        {
            shbab[Subs[node]]--;
            Nde=order[node];
            delet();
            Nde=Subs[node];
        int v=search_();
            ans+=cnt[v]-shbab[Subs[node]];
        }
        if(shbab[Subs[node]])ans1++;
        printf("%d %d\n",ans1,ans);
        //cout<<ans1<<' '<<ans<<'\n';
    }
    return 0;
}