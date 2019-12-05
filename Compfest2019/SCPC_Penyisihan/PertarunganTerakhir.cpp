#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MOD = 1000000007;

int m, n;
int a[N], b[N];

int pre[N][N];

int dp[N][N];
int f(int x, int y) {
  if (y < 0) return 0;
  if (x == m) return y == n;
  if (y == n) return f(x, y-1);
  if (~dp[x][y]) return dp[x][y];

  int r = upper_bound(pre[y], pre[y] + n, b[x]) - pre[y];
  int l = lower_bound(pre[y], pre[y] + n, b[x]) - pre[y];

  int ret = f(x+1, r) - f(x+1, l);
  if (ret < 0) ret += MOD;

  ret = (ret + f(x, y-1)) % MOD;
  return dp[x][y] = ret;
}

int main() {
  scanf("%d %d", &n, &m);
  assert(1 <= m && m <= n && n <= 2000);
  for (int i = 0; i < n; ++i) assert(scanf("%d", a + i) == 1);
  for (int i = 0; i < m; ++i) assert(scanf("%d", b + i) == 1);

  for (int i = 0; i < n; ++i) {
    pre[i][i] = a[i];
    for (int j = i+1; j < n; ++j) {
      pre[i][j] = max(a[j], pre[i][j-1]);
    }
  }

  memset(dp, -1, sizeof dp);

  printf("%d\n", f(0, 0));
  return 0;
}
