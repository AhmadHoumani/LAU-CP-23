#include <bits/stdc++.h>
using namespace std;

typedef vector<long double> vec;
typedef vector<vec> mat;

const long double EPS = 1e-13;

int deg[20];

vec GaussianElimination(const mat& A, const vec& b) {
	int i, j, k, pivot, n = A.size();
	mat B(n, vec(n+1));
	vec x(n);
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) B[i][j] = A[i][j];
		B[i][n] = b[i];
	}
	for(i = 0; i < n; i++) {
		for(pivot = j = i; j < n; ++j) if(fabs(B[j][i]) > fabs(B[pivot][i])) pivot = j;
		swap(B[i], B[pivot]);
		if(fabs(B[i][i]) < EPS) return vec();
		for(j = n; j >= i; --j) B[i][j] /= B[i][i];
		for(j = 0; j < n; j++) if(i != j) for(k = i+1; k <= n; ++k) B[j][k] -= B[j][i] * B[i][k];
	}
	for(i = 0; i < n; i++) x[i] = B[i][n];
	return x;
}
