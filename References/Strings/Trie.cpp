#include<bits/stdc++.h>
#define P(x,y) make_pair(x,y)
using namespace std;
struct node;
typedef node* pnode;
struct node{
    int cnt;
    bool isend;
    vector < pair < char , pnode > > child;
    node(){ cnt=isend=0; child.clear(); }
};
class Trie{
    public:
    pnode head;
    void init(){
        head = new node();
    }
    void insert_(string &str){
        pnode it = head;
        it->cnt++;
        for(auto let : str){
            bool ok=0;
            for(auto nxt : it->child){
                if(nxt.first == let){
                    it = nxt.second;
                    ok = 1;
                    break;
                }
            }
            if(!ok){
                it->child.push_back(P(let , new node()));
                it = it->child.back().second;
            }
            it->cnt++;
        }
        it->isend=1;
    }
    bool find_(string &str){
        pnode it = head;
        for(auto let : str){
            bool ok=0;
            for(auto nxt : it->child){
                if(nxt.first == let){
                    it = nxt.second;
                    ok = 1;
                    break;
                }
            }
            if(!ok) return 0;
        }
        return it->isend;
    }
};




#include<bits/stdc++.h>
#define P(x,y) make_pair(x,y)
using namespace std;
struct node;
typedef node* pnode;
struct node{
    int cnt;
    bool isend;
    pnode child[26];
    node(){ cnt=isend=0; memset(child , 0 , sizeof(child)); }
};
class Trie{
    public:
    pnode head;
    void init(){
        head = new node();
    }
    void insert_(string &str){
        pnode it = head;
        it->cnt++;
        for(auto ch : str){
            int let = ch-'a';
            if(it->child[let] == NULL) it->child[let] = new node();
            it = it->child[let];
            it->cnt++;
        }
        it->isend=1;
    }
    bool find_(string &str){
        pnode it = head;
        for(auto ch : str){
            int let = ch - 'a';
            if(it->child[let] == NULL) it->child[let] = new node();
            it = it->child[let];
        }
        return it->isend;
    }
};
int main(){
}
