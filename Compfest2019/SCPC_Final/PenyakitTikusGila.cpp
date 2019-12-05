#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 1000000007;

int n;
int sum[N][N];
int two[200005];

int count(int x, int y, int xx, int yy) {
  return sum[xx][yy] - sum[x-1][yy] - sum[xx][y-1] + sum[x-1][y-1];
}

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  
  return ret;
}

void solve() {
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= 1000; ++j) {
      sum[i][j] = 0;
    }
  }
  
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    ++sum[x][y];
  }
  
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= 1000; ++j){ 
      sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
    }
  }
  
  int ans = 0;
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= 1000; ++j) {
      long long cur = two[n] - 1;
      cur -= two[count(1, 1, 1000, i-1)] - 1;
      cur -= two[count(1, 1, j-1, 1000)] - 1;
      cur -= two[count(1, j+1, 1000, 1000)] - 1;
      cur -= two[count(i+1, 1, 1000, 1000)] - 1;
      cur += two[count(1, j+1, i-1, 1000)] - 1;
      cur += two[count(1, 1, i-1, j-1)] - 1;
      cur += two[count(i+1, 1, 1000, j-1)] - 1;
      cur += two[count(i+1, j+1, 1000, 1000)] - 1;
      
      cur %= MOD;
      if (cur < 0) cur += MOD;
      
      ans = (ans + cur) % MOD;
    }
  }
  
  ans = 1LL * ans * power(two[n], MOD-2) % MOD;
  printf("%d\n", ans);
}

int main() {
  two[0] = 1;
  for (int i = 1; i <= 200000; ++i) two[i] = two[i-1] * 2 % MOD;

  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
