#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

const int N = 2005;

int n;
int a[N];

int fact[N];
int C[N][N];
void init() {
  C[0][0] = 1;
  for (int i=1; i<N; i++) {
    C[i][0] = 1;
    for (int j=1; j<=i; j++) {
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
  }
  
  fact[0] = 1;
  for (int i=1; i<N; i++) fact[i] = 1LL * i * fact[i-1] % MOD;
}

int main() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) scanf("%d", a + i);
  
  init();
  
  if (n == 2) {
    if (a[0] != a[1]) printf("0\n");
    else printf("%d\n", fact[a[0]]);
    return 0;
  }
  
  int ans = 0;
  for (int i=0; i<=min(a[0], a[n-1]); i++) {
    int sum = 1;
    
    int prv = a[0] - i;
    for (int j=1; j<n; j++) {
      if (prv > a[j]) {
        sum = 0;
        break;
      }
      
      sum = 1LL * sum * C[a[j]][prv] % MOD * fact[prv] % MOD;
      prv = a[j] - prv;
    }
    
    if (prv != i) sum = 0;
    else sum = 1LL * sum * C[a[0]][i] % MOD * fact[i] % MOD;
    
    ans = (1LL * ans + sum) % MOD;
  }
  
  printf("%d\n", ans);
  
  return 0;
}