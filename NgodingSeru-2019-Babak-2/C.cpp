#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int LN = 16;

int n, q;
vector<int> edges[N];
int grup[N];

namespace Centroid {

int par_centroid[N];
int size[N];
bool removed[N];

void compute_subtree(int u, int p=-1) {
  size[u] = 1;
  for (int v: edges[u]) {
    if (v == p || removed[v]) continue;
    compute_subtree(v, u);
    size[u] += size[v];
  }
}

int find_centroid(int u) {
  compute_subtree(u);
  int tree_size = size[u];
  
  bool found = false;
  while (!found) {
    found = true;
    for (int v: edges[u]) {
      if (removed[v] || size[v] > size[u]) continue;
      if (size[v] > tree_size/2) {
        found = false;
        u = v;
        break;
      }
    }
  }
  
  return u;
}

int build_centroid_tree(int u) {
  u = find_centroid(u);
  removed[u] = true;

  for (int v: edges[u]) {
    if (!removed[v]) {
      v = build_centroid_tree(v);

      par_centroid[v] = u;
    }
  }

  return u;
}

}

namespace LCA {
  
int depth[N];
int par[LN][N];

void dfs(int u, int p) {
  par[0][u] = p;
  for (int v: edges[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}

void build_lca() {
  depth[0] = 0;  
  dfs(0, 0);
  
  for (int i=1; i<LN; i++) for (int j=0; j<n; j++) {
    par[i][j] = par[i-1][par[i-1][j]];
  }
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  while (depth[u] != depth[v]) {
    u = par[__builtin_ctz(depth[u] - depth[v])][u];
  }
  
  if (u == v) return u;
  for (int i=LN-1; i>=0; i--) {
    if (par[i][u] != par[i][v]) {
      u = par[i][u];
      v = par[i][v];
    }
  }
  
  return par[0][u];
}

int dist(int u, int v) {
  return depth[u] + depth[v] - depth[lca(u, v)] * 2;
}

}

using namespace Centroid;
using namespace LCA;

void read() {
  scanf("%d %d", &n, &q);
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  
  for (int i=0; i<n; i++) scanf("%d", grup + i);
}

long long sum[N], sump[N];
int cnt[N];
void solve() {
  build_lca();
  
  int root_centroid = build_centroid_tree(0);
  par_centroid[root_centroid] = -1;
  
  long long ans = 0;
  
  auto add = [&](int u) {
    long long cur_sum = 0;
    int cur_cnt = 0;
    for (int v = u, pv = v; v != -1; pv = v, v = par_centroid[v]) {
      cnt[v] += 1;
      sum[v] += dist(u, v);
      if (par_centroid[v] != -1) sump[v] += dist(u, par_centroid[v]);
      
      cur_sum = sum[v] - (pv != v ? sump[pv] : 0);
      cur_cnt = cnt[v] - (pv != v ? cnt[pv] : 0);
      
      ans += cur_sum + 1LL * dist(u, v) * cur_cnt;
    }
  };
  
  auto erase = [&](int u) {
    long long cur_sum = 0;
    int cur_cnt = 0;
    for (int v = u, pv = v; v != -1; pv = v, v = par_centroid[v]) {
      cnt[v] -= 1;
      sum[v] -= dist(u, v);
      if (par_centroid[v] != -1) sump[v] -= dist(u, par_centroid[v]);
      
      cur_sum = sum[v] - (pv != v ? sump[pv] : 0);
      cur_cnt = cnt[v] - (pv != v ? cnt[pv] : 0);
      
      ans -= cur_sum + 1LL * dist(u, v) * cur_cnt;
    }
  };
  
  for (int i=0; i<n; i++) if (grup[i]) add(i);
  
  while (q--) {
    int t;
    scanf("%d", &t);
    
    if (t == 1) {
      printf("%lld\n", ans);
    } else if (t == 2) {
      int u;
      scanf("%d", &u);
      --u;
      
      if (grup[u] == 0) add(u);
      else erase(u);
      
      grup[u] ^= 1;
    }
  }
}

int main() {
  read();
  solve();
  return 0;
}
