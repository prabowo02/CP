#include <bits/stdc++.h>
using namespace std;

const int N = 8005;

int n;
double p;

bool vis[N][N];
double dp[N][N];
double f(int x, int y) {
  if (y > x) return 0;
  if (y <= 0) return 0;
  if (x == 1) return 0;
  if (vis[x][y]) return dp[x][y];
  vis[x][y] = true;

  double ret = 1;
  ret += f(x-1, y-1)                           * ((double) (y-1) / x * (y-2) / (x-1));
  ret += f(x-1, y)                             * ((double) (x-y) / x * (x-y-1) / (x-1));
  ret += (p * f(x-1, y-1))                     * (2.0 * (y-1) / x / (x-1));
  ret += ((1-p) * f(x-1, y))                   * (2.0 * (x-y) / x / (x-1));
  ret += (p * f(x-1, y-1) + (1-p) * f(x-1, y)) * (2.0 * (y-1) / x * (x-y) / (x-1));
  return dp[x][y] = ret;
}

void read() {
  scanf("%d %lf", &n, &p);
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) vis[i][j] = false;
  for (int i = 1; i <= n; ++i) {
    printf("%.8lf\n", f(n, i));
  }
}

int solve() {
  read();
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d:\n", tc+1);
    solve();
  }
  return 0;
}
