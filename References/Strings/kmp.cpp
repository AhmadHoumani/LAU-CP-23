#include<bits/stdc++.h>
using namespace std;
int lps[1<<17];
string s;
void calclps()
{
    lps[0]=-1;
    int len=s.size();
    for(int i=1;i<len;++i)
    {
        int j=lps[i-1];
        lps[i]=-1;
        while(1)
        {
            if(s[i]==s[j+1]){lps[i]=j+1;break;}
            if(j==-1)break;
            j=lps[j];
        }
    }
}
int main()
{
    cin>>s;
    calclps();
    for(int i=0;i<s.size();++i)cout<<lps[i]<<" ";
}
