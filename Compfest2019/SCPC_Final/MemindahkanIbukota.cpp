#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
pair<int, int> a[N];

int dp[N];
int f(int x) {
  if (x == m) return 0;
  if (~dp[x]) return dp[x];
  
  int idx = lower_bound(a, a + m, make_pair(a[x].second, -1)) - a;
  return dp[x] = min(f(x+1) + a[x+1].first - a[x].first, f(idx) + a[idx].first - a[x].second + 1);
}

int solve() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &a[i].first, &a[i].second);
  }
  
  sort(a, a + m);
  a[m] = {n, 0};
  
  for (int i = 0; i < m; ++i) dp[i] = -1;
  printf("%d\n", a[0].first-1 + f(0));
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }

  return 0;
}
