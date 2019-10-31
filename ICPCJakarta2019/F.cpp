#include <bits/stdc++.h>
using namespace std;

const int N = 4004;

int n;
vector<int> edges[N];

int sz[N];
bool used[N];
void dfs(int u, int p=-1) {
  sz[u] = 1;
  for (int v: edges[u]) {
    if (v == p || used[v]) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}

int get_centroid(int root) {
  int cur = root, par = -1;
  while (true) {
    bool found = true;

    for (int v: edges[cur]) {
      if (v == par || used[v]) continue;

      if (sz[v] > sz[root] / 2) {
        found = false;
        par = cur; cur = v;
        break;
      }
    }

    if (found) return cur;
  }

  return -1;
}

namespace TreeHash {

const int HASH_SIZE = 2;
const int MOD[HASH_SIZE] = {1004535809, 998244353};
const int BASE[HASH_SIZE] = {360133888, 412820665};

vector<int> hash_tree(int u, int p=-1) {
  vector<int> result(HASH_SIZE, 1);

  vector<vector<int>> children;
  for (int v: edges[u]) {
    if (v == p || used[v]) continue;

    children.push_back(hash_tree(v, u));
  }
  sort(children.begin(), children.end());

  for (const vector<int> &child: children) {
    for (int i = 0; i < HASH_SIZE; ++i) {
      result[i] = (1LL * result[i] * BASE[i] + child[i]) % MOD[i];
    }
  }

  return result;
}

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

  dfs(0);
  int good = get_centroid(0);
  used[good] = true;

  dfs(good);
  pair<vector<int>, vector<int>> tree;
  for (int v: edges[good]) {
    if (sz[v] != sz[edges[good][0]]) return 0 * printf("-1\n");

    int centroid = get_centroid(v);
    int centroid2 = centroid;

    for (int vv: edges[centroid]) {
      if (!used[vv] && sz[vv] * 2 == sz[v]) {
        centroid2 = vv;
        break;
      }
    }

    pair<vector<int>, vector<int>> h = {TreeHash::hash_tree(centroid), TreeHash::hash_tree(centroid2)};
    if (h.second < h.first) swap(h.first, h.second);

    if (tree.first.size() == 0) tree = h;
    else if (tree != h) return 0 * printf("-1\n");
  }

  printf("%d\n", (int) edges[good].size());
  return 0;
}
