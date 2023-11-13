#include <bits/stdc++.h>
using namespace std;

namespace HopcroftKarp {

int n1, n2;

vector<vector<int>> adj;
vector<int> dist, match;
vector<bool> vis, matched;

void init(int _n1, int _n2) {
  n1 = _n1;
  n2 = _n2;
  adj.resize(n1);
}

void addEdge(int u, int v) {
  adj[u].push_back(v);
}

void bfs() {
  dist.assign(n1, -1);
  queue<int> q;
  for (int u = 0; u < n; ++u) {
    if (!matched[u]) {
      q.push(u);
      dist[u] = 0;
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
      if (match[v] >= 0 && dist[match[v]] == -1) {
        dist[match[v]] = dist[u] + 1;
        q.push(match[v]);
      }
    }
  }
}

int dfs(int u) {
  if (vis[u]) return false;
  vis[u] = true;
  for (int v : adj[u]) {
    if (match[v] == -1 || dist[match[v]] == dist[u] + 1 && self(self, match[v])) {
      match[v] = u;
      matched[u] = true;
      return true;
    }
  }
  return false;
}

int maxMatch() {
  matched.assign(n1, false);
  match.assign(n2, -1);
  int ret = 0;
  while (true) {
    vis.assign(n1, false);
    bfs();
    int flow = 0;
    for (int u = 0; u < n; ++u) {
      if (!matched[u] && dfs(dfs, u)) {
        ++flow;
      }
    }
    if (!flow) break;
    ret += flow;
  }
  return ret;
}

int maxMatch(vector<vector<int>> &_adj) {
  swap(adj, _adj);
  int n = adj.size();
  init(n, n);
  int ret = maxMatch();
  swap(adj, _adj);
  return ret;
}

}

int main() {
  HopcroftKarp::init(2, 3);
  HopcroftKarp::addEdge(0, 1);
  HopcroftKarp::addEdge(1, 1);
  printf("%d\n", HopcroftKarp::maxMatch());

  // Or, if you have vector<vector<int>> adj
  printf("%d\n", HopcroftKarp::maxMatch(adj));
  return 0;
}
