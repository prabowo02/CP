#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
const int MOD = 1000000007;

int n;
int h[N];

int a[N];
int cnt[N];

struct Matrix {
  int a[100][100];
  
  Matrix(int val=0) {
    for (int i=0; i<100; i++) {
      for (int j=0; j<100; j++) {
        a[i][j] = 0;
      }
      a[i][i] = val;
    }
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret;
    for (int i=0; i<100; i++) {
      for (int j=0; j<100; j++) {
        for (int k=0; k<100; ++k) {
          ret.a[i][j] = (1LL * a[i][k] * other.a[k][j] + ret.a[i][j]) % MOD;
        }
      }
    }
    
    return ret;
  }
};

Matrix jump[22];

int main() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    scanf("%d", h + i);
    ++cnt[--h[i]];
  }
  
  for (int i=0; i<100; ++i) for (int j=0; j<100; j++) {
    if (i >= j) jump[0].a[i][j] = cnt[i];
    else jump[0].a[i][j] = 0;
  }
  
  for (int i=1; i<22; i++) {
    jump[i] = jump[i-1] * jump[i-1];
    
    // if (i <= 2) for (int ii=0; ii<5; ii++) { for (int jj=0; jj<5; jj++) cerr << jump[i].a[ii][jj] << " "; cerr << endl; }
  }
  
  int q; scanf("%d", &q);
  while (q--) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    --x, --y, --z;
    
    if (h[x] > h[y]) {
      printf("0\n");
      continue;
    }
    
    if (z == -1) {
      if (x == y) printf("1\n");
      else printf("0\n");
      continue;
    }
    
    int a[2][100];
    for (int i=0; i<100; i++) {
      a[0][i] = 0;
    }
    a[0][h[x]] = 1;
    
    int now = 0;
    while (z > 0) {
      int bit = __builtin_ctz(z);
      z -= 1 << bit;
      now ^= 1;
      
      for (int i=0; i<100; i++) {
        a[now][i] = 0;
        for (int j=0; j<100; j++) {
          a[now][i] = (1LL * a[now^1][j] * jump[bit].a[i][j] + a[now][i]) % MOD;
        }
      }
    }
    
    int ans = 0;
    for (int i=h[x]; i<=h[y]; i++) ans = (a[now][i] + ans) % MOD;
    printf("%d\n", ans);
  }
  
  return 0;
}
