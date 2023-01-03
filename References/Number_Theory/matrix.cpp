#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdio>
#define Matrix vector< vector < int > >
using namespace std;
void Resize_Matrix(int n , int m , Matrix &M){
    while(n--) M.push_back( vector<int>(m,0) );
}
Matrix Matrix_Multiplication(Matrix A , Matrix B){
    Matrix Ans; int n , m;
    Resize_Matrix(n=A.size() , m=A[0].size() , Ans);
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++){
            Ans[j][i]=0;
            for(int k=0;k<m;k++){
                Ans[j][i]+= A[j][k]*B[k][i];
            }
        }
    }
    return Ans;
}
Matrix Matrix_Exponentiation(Matrix M , int power){
    if(power==1) return M;
    Matrix ret=Matrix_Exponentiation(M , power/2);
    ret=Matrix_Multiplication(ret , ret);
    if(power%2) ret=Matrix_Multiplication(ret , M);
    return ret;
}
int main(){
    int n , T;
    cin>>n>>T;
    Matrix M; Resize_Matrix(n,n,M);
    for(int j=0;j<n;j++) for(int i=0;i<n;i++) if(j!=i) M[j][i]=1;
    M=Matrix_Exponentiation(M,T);
    Matrix Ans; Resize_Matrix(n,n,Ans);
    for(int j=0;j<n;j++) cin>>Ans[0][j];
    Ans=Matrix_Multiplication(Ans,M);
    for(int j=0;j<n;j++) cout<<Ans[0][j]<<endl;
}
