#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

vector<int> edges[N];
int disc[N], low[N], child[N];

int t = 0;
void dfs(int u, int parent) {
  disc[u] = low[u] = t++;
  for (int v: edges[u]) {
    if (disc[v] == -1) {
      ++child[u];
      dfs(v, u);
      if (low[v] > disc[u]) {
        // (u, v) is bridge
      }
      if (low[v] >= disc[u]) {
        // u is articulation point
      }
      low[u] = min(low[u], low[v]);
    } else if (v != parent) {
      low[u] = min(low[u], disc[v]);
    }
  }
}

int main() {
  int root = 0;
  dfs(root, -1);

  // Special case
  if (child[root] < 2) {
    // root is not articulation point
  } else {
    // root is articulation point
  }

  return 0;
}