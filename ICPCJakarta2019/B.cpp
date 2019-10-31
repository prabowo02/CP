#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MOD = 1000000007;

int n;
vector<int> edges[N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  
  return ret;
}

int inv(int x) {
  return power(x, MOD-2);
}

// 0: parent is middle of a path
// 1: parent has path to current
// 2: parent is end of a path

int dp[N][3];
int f(int u, int p, int st) {
  if (~dp[u][st]) return dp[u][st];

  for (int &v: edges[u]) {
    if (v == p) swap(v, edges[u].back());
  }

  long long ret = 0;

  vector<int> prod0(edges[u].size()), prod2(edges[u].size());
  prod0.back() = prod2.back() = 1;
  for (int i = (int) edges[u].size() - 2; i >= 0; --i) {
    int v = edges[u][i];

    prod0[i] = 1LL * prod0[i+1] * f(v, u, 0) % MOD;
    prod2[i] = 1LL * prod2[i+1] * f(v, u, 2) % MOD;
  }

  if (st == 0 || st == 1) {
    ret = ret + prod2[0];
  }

  int pre0 = 1, pre2 = 1;
  int sum = 0;
  for (int i = 0; i+1 < edges[u].size(); ++i) {
    int v = edges[u][i];

    if (st == 0) {
      ret = 1LL * pre2 * f(v, u, 1) % MOD * prod2[i+1] % MOD + ret;
    }
    if (st == 1) {
      ret = 1LL * pre0 * f(v, u, 1) % MOD * prod0[i+1] % MOD + ret;
    }
    if (st == 0 || st == 2) {
      ret = 1LL * sum * f(v, u, 1) % MOD * prod0[i+1] % MOD + ret;
      sum = (1LL * sum * f(v, u, 0) + 1LL * pre0 * f(v, u, 1)) % MOD;
    }

    pre0 = 1LL * pre0 * f(v, u, 0) % MOD;
    pre2 = 1LL * pre2 * f(v, u, 2) % MOD;
  }

  // cerr << u+1 << " " << st << " " << ret << endl;
  return dp[u][st] = ret % MOD;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  edges[0].push_back(-1);
  memset(dp, -1, sizeof dp);
  printf("%d\n", f(0, 0, 0));
  return 0;
}
