#include<bits/stdc++.h>
using namespace std;
int timer;
struct node{
    int nxt[26] , fail , link[26];
    vector < int > who;
    node(){
        memset(nxt , -1 , sizeof(nxt));
        memset(link , -1 , sizeof(link));
        fail = -1;
        who.clear();
    }
};
int ans[1000];
class Aho_Corasick{
    int head , timer;
    node trie[1<<19];
    public:
    void init(){
        head = timer = 0;
        trie[head] = node();
    }
    void insert_(string str , int idx){
        int cur = head;
        for(int i=0;i<str.size();++i){
            int let = str[i] - 'a';
            if(trie[cur].nxt[let] == -1){
                trie[cur].nxt[let] = ++timer;
                //cout<<ch<<" "<<timer<<endl;
                trie[timer] = node();
            }
            cur = trie[cur].nxt[let];
        }
        trie[cur].who.push_back(idx);
    }
    void build(){
        queue < int > Q;
        trie[head].fail = head;
        for(int let = 0 ; let < 26 ; let++){
            if(trie[head].nxt[let] == -1) continue;
            int x = trie[head].nxt[let];
            trie[head].link[let]=x;
            trie[x].fail = head;
            Q.push(x);
        }
        while(!Q.empty()){
            int cur = Q.front(); Q.pop();
            //cout<<"build "<<cur<<endl;
            for(int let = 0 ; let < 26 ; let++){
                if(trie[cur].nxt[let] == -1) continue;
                int nxt = trie[cur].nxt[let];
                trie[nxt].fail = head;
                int ptr = trie[cur].fail;
                while(1){
                    if(trie[ptr].nxt[let] != -1){
                        trie[nxt].fail = trie[ptr].nxt[let];
                        break;
                    }
                    if(ptr == head) break;
                    ptr = trie[ptr].fail;

                }
                Q.push(nxt);
           }
           int F = trie[cur].fail;
           for(int j = 0 ; j < trie[F].who.size(); j++)
               trie[cur].who.push_back(trie[F].who[j]);
           for(int let = 0 ; let < 26 ; let ++){
               trie[cur].link[let] = trie[F].link[let];
               if(trie[cur].nxt[let] != -1)
                   trie[cur].link[let] = trie[cur].nxt[let];
           }
       }
    }
    void ask(string s){
        int curr=head;
        for(int i=0;i<s.size();++i){
            curr=trie[curr].link[s[i]-'a'];
            if(curr==-1)curr=trie[head].link[s[i]-'a'];
            if(curr==-1){curr=head;continue;}
            //cout<<curr<<" "<<trie[curr].who.size()<<endl;
            for(int j=0;j<trie[curr].who.size();++j)++ans[trie[curr].who[j]];
        }

    }
};
char a[1000005],b[1000];
Aho_Corasick x;
int main(){
    int t,tc=1;
    cin>>t;
    string s,s1;
    while(t--){
        int n;
        cin>>n;
        scanf("%s",a);s1=a;
        x.init();
        for(int i=1;i<=n;++i){
            scanf("%s",b);
            s=b;
            x.insert_(s,i);
        }

        memset(ans,0,sizeof ans);
        x.build();
        x.ask(s1);
        printf("Case %d:\n",tc++);
        for(int i=1;i<=n;++i)cout<<ans[i]<<endl;
    }
}



