#include<bits/stdc++.h>
using namespace std;
struct node;
typedef node* pnode;
struct node{
    int key , prior , freq , cnt;
    pnode l , r;
    static pnode empt;
    node(){
        key=prior=freq=cnt=0;
        l=r=this;
    }
    node(int V){
        key = V; prior = rand(); freq=cnt=1;
        l=r=empt;
    }
};
pnode node::empt = new node();
pnode dummy = node::empt;
class Treap{
    pnode root;
    private:
    void update(pnode &it){
        it->cnt = it->l->cnt + it->r->cnt + it->freq;
    }
    void split(pnode it , int K , pnode&l , pnode&r){
        if(it == dummy)
            l = r = dummy;
        else if(it->key > K)
            split(it->l , K , l , it->l) , r = it; // pay attention
        else
            split(it->r , K , it->r , r) , l = it; // these are , not ;
        update(it);
    }
    void merge_(pnode &it , pnode l , pnode r){
        if(l==dummy || r==dummy)
            it = (l==dummy)? r : l;
        else if(l->prior > r->prior) merge_(l->r , l->r , r) , it=l;
        else merge_(r->l , l , r->l) , it=r;
        update(it);
    }
    void insert_(pnode &it, pnode item) {
        if (it == dummy)
            it = item;
        else if(item -> prior > it -> prior)
            split(it , item->key , item->l , item->r) , it = item;
        else insert_(it->key > item->key ? it->l : it->r , item);
        update(it);
    }
    void erase_(pnode &it , int K){
//        cout<<it->key<<endl;
        if(it->key == K) merge_(it , it->l , it->r);
        else erase_(it->key > K ? it->l : it->r , K);
        update(it);
    }
    void inc(pnode it , int K , int V){
        if(it->key == K) it->freq += V;
        else inc(it->key > K ? it->l : it->r , K , V);
        update(it);
    }
    int find_(pnode it , int K){
        if(it == dummy) return 0;
        if(it->key == K) return it->freq;
        return find_(it->key > K ? it->l : it->r , K);
    }
    int Kth(pnode it , int K){
        if(it->l->cnt >= K) return Kth(it->l , K);
        if(it->l->cnt + it->freq < K) return Kth(it->r , K-it->l->cnt-it->freq);
        return it->key;
    }
    int countless(pnode it , int K){
        if(it == dummy) return 0;
        if(it->key > K) return countless(it->l , K);
        return it->l->cnt + it->freq + countless(it->r , K);
    }
    void Clear( pnode &it ){
        if(!it || it == dummy) return;
        Clear(it->l); Clear(it->r);
        delete(it);
    }
    public:
    //////////////////////////////////////////////////////
    // these are the functions you call

    void init(){
        Clear(root);
        root = dummy;
    }

    void Insert(int K){
        if(find_(root , K)) inc(root , K , 1);
        else insert_(root , new node(K));
    }
    void Delete(int K){
        int tt = find_(root , K);
        if(tt > 1) inc(root , K , -1);
        else if(tt==1) erase_(root , K);
    }
    int Count(int K){ // you can use count as a find :D
        return find_(root , K);
    }
    int Get_Kth(int K){
        return Kth(root , K);
    }
    int Rank(int K){ // this function returns how many elements less than or equal
        return countless(root , K);
    }
    int Size(){
        return root->cnt;
    }
} ;
