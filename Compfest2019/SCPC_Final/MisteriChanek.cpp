#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
char s[N][N];
int M[N][N];

int par[N];
int dsu(int u) {
  if (u == par[u]) return u;
  return par[u] = dsu(par[u]);
}

vector<pair<int, int>> build_mst() {
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      edges.emplace_back(M[i][j], i, j);
    }
  }
  
  sort(edges.begin(), edges.end());

  for (int i = 0; i < n; ++i) par[i] = i;

  vector<pair<int, int>> ret;
  for (const tuple<int, int, int> &edge: edges) {
    int w, u, v;
    tie(w, u, v) = edge;

    if (dsu(u) == dsu(v)) continue;

    par[dsu(u)] = dsu(v);
    ret.emplace_back(u, v);
  }

  return ret;
}

vector<int> adj[N];
void build_adj(const vector<pair<int, int>> &edges) {
  for (const pair<int, int> &edge: edges) {
    adj[edge.first].push_back(edge.second);
    adj[edge.second].push_back(edge.first);
  }
}

vector<int> bfs(int u, const vector<pair<int, int>> &edges) {
  vector<int> dist(n, -1);

  dist[u] = 0;
  queue<int> q;
  q.push(u);

  while (q.size()) {
    int u = q.front();
    q.pop();

    for (int v: adj[u]) {
      if (dist[v] >= 0) continue;
      dist[v] = dist[u] + M[u][v];
      q.push(v);
    }
  }

  return dist;
}

bool is_connected(const vector<pair<int, int>> &edges) {
  vector<int> dist = bfs(0, edges);
  return all_of(dist.begin(), dist.end(), [](int d){ return d >= 0; });
}

vector<int> deg;
bool is_path(const vector<pair<int, int>> &edges) {
  deg = vector<int>(n, 0);
  for (const pair<int, int> edge: edges) {
    ++deg[edge.first];
    ++deg[edge.second];
  }

  if (n == 1) return deg[0] == 0;

  int cnt1 = 0;
  for (int d: deg) {
    if (d == 1) ++cnt1;
    else if (d != 2) return false;
  }

  if (cnt1 != 2) return false;
  return true;
}

bool is_consistent(const vector<pair<int, int>> &edges) {
  for (int i = 0; i < n; ++i) {
    vector<int> dist = bfs(i, edges);
    for (int j = 0; j < n; ++j) {
      if (dist[j] != M[i][j]) return false;
    }
  }

  return true;
}

bool is_message_consistent(const vector<int> &path) {
  auto dist = [](int u, int v) {
    int ret = 0;
    int i = 0;
    for (; s[u][i] && s[v][i]; ++i) {
      if (s[u][i] != s[v][i]) ++ret;
    }

    for (int j = i; s[u][j]; ++j) ++ret;
    for (int j = i; s[v][j]; ++j) ++ret;

    return ret;
  };

  for (int i = 1; i < path.size(); ++i) {
    if (dist(path[i-1], path[i]) != M[path[i-1]][path[i]]) return false;
  }

  return true;
}

vector<int> build_path(vector<pair<int, int>> edges) {
  if (n == 1) return {0};

  vector<vector<int>> adj(n);
  for (const pair<int, int> &edge: edges) {
    adj[edge.first].push_back(edge.second);
    adj[edge.second].push_back(edge.first);
  }

  int cur = -1;
  for (int i = 0; i < n; ++i) {
    if (adj[i].size() == 1) {
      cur = i;
      break;
    }
  }

  vector<int> ret;
  ret.push_back(cur);
  cur = adj[cur][0];

  while (adj[cur].size() != 1) {
    ret.push_back(cur);
    if (adj[cur][0] == ret[ret.size() - 2]) cur = adj[cur][1];
    else cur = adj[cur][0];
  }

  ret.push_back(cur);
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &M[i][j]);
    }
  }

  vector<pair<int, int>> mst = build_mst();

  build_adj(mst);

  if (!is_connected(mst) || !is_path(mst) || !is_consistent(mst)) {
    return 0 * printf("Aku sudah menyangka tidak akan semudah ini Ferguso\n");
  }

  vector<int> path = build_path(mst);

  if (!is_message_consistent(path)) {
    return 0 * printf("Aku sudah menyangka tidak akan semudah ini Ferguso\n");
  }

  for (int i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    printf("%s", s[path[i]]);
  }
  printf("\n");

  return 0;
}
