#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int MOD = 1000000007;

int n, r, c, k;

int p[N];
int row[N], col[N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  
  return ret;
}

void build(int n, int a[]) {
  for (int i=1; i<=n; i++) for (int j=1; j<=n-i+1; j++) {
    int len = n - i - j + 2;
    a[len] = (1LL * p[i] * p[j] + a[len]) % MOD;
  }
  
  for (int i=1; i<n; i++) a[i] = (a[i] - a[i+1] + MOD) % MOD;
  for (int i=1; i<n; i++) a[i] = (a[i] - a[i+1] + MOD) % MOD;
}

int main() {
  scanf("%d %d %d %d", &n, &r, &c, &k);
  
  for (int i=1; i<N; i++) p[i] = power(i, n);
  
  build(r, row); build(c, col);
  
  for (int i=c-1; i>0; i--) col[i] = (col[i] + col[i+1]) % MOD;
  
  int ans = 0;
  for (int i=1; i<=r; i++) {
    int cc = (k + i - 1) / i;
    if (cc > c) continue;
    
    ans = (1LL * row[i] * col[cc] + ans) % MOD;
  }
  
  printf("%d\n", ans);
  
  return 0;
}
