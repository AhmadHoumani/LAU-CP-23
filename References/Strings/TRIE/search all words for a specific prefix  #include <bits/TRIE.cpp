// TRIE
// search all words for a specific prefix

#include <bits/stdc++.h>
using namespace std;
char st[25001][20];
int a[22001], counter=0;
struct Node{
    Node *ch[26];
    bool isend;
    int cnt;
    Node(){
        isend=false;
        for(int i=0; i<26; ++i){
            ch[i]=0;
        }
        cnt=0;
    }
}*root;
void insert_(char *str, int idx){
    int let;
    Node *it=root;
    for(int i=0; str[i]!='\0'; ++i){
        let=str[i]-'a';
        if(!it->ch[let]){
            it->ch[let]=new Node();
        }
        it=it->ch[let];
    }
    it->isend=1;
    it->cnt=idx;
}
void loop(Node *ptr){
    if(ptr->isend){
        a[counter++]=ptr->cnt;
    }
    for(int i=0; i<26; ++i){
        if(ptr->ch[i]){
            loop(ptr->ch[i]);
        }
    }
}
void find_(char *str){
    int let;
    Node *it=root;
    for(int i=0; str[i]!='\0'; ++i){
        let=str[i]-'a';
        if(!(it->ch[let])){
            return;
        }
        it=it->ch[let];
    }
    for(int i=0; i<26; ++i){
        if(it->ch[i]){
            loop(it->ch[i]);
        }
    }
}
int main(){
int n, k;
char c[20];
while(cin>>n){
    root=new Node();
    int cnt=0;
    for(int i=0; i<n; ++i){
        scanf("%s", c);
        for(int j=0;c[j]!='\0'; ++j)
            st[cnt][j]=c[j];
        ++cnt;
        insert_(c, i);
    }
    cin>>k;
    for(int j=1; j<=k; ++j){
        counter=0;
        printf("Case #%d:\n", j);
        scanf("%s", c);
        find_(c);
        if(counter>0){
            for(int i=0; i<counter; ++i){
                printf("%s\n",st[a[i]]);
            }
        }
        else{
            printf("No match.\n");
        }
    }
}
return 0;
}
