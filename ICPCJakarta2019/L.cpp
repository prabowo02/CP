#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, k;
int a[N];
vector<int> b[N];
int c[N];

vector<int> edges[N];

bool vis[N], vis2[N];;
int par[N];
bool cycle[N];
void dfs(int u, int p) {
  vis[u] = true;
  vis2[u] = true;
  par[u] = p;
  for (int v: edges[u]) {
    if (v == p) continue;

    if (vis[v]) {
      int cur = u;
      while (cur != v) {
        cycle[cur] = true;
        cur = par[cur];
      }
      cycle[cur] = true;
      continue;
    }
    if (vis2[v]) continue;

    dfs(v, u);
  }
  vis[u] = false;
}

const int NN = 25005;
const int INF = 1000000000;

struct Dinic {
  int s, t;
  vector<int> edges[NN], cap[NN], rev[NN];
  int dist[NN], it[NN];
  
  void addEdge(int u, int v, int c) {
    if (u == v) return;

    rev[u].push_back(edges[v].size());
    cap[u].push_back(c);
    edges[u].push_back(v);

    rev[v].push_back((int) edges[u].size() - 1);
    cap[v].push_back(0);
    edges[v].push_back(u);
  }
  
  bool bfs() {
    queue<int> q;
    q.push(s);
    
    for (int i=0; i<=t; i++) dist[i] = -1;
    dist[s] = 0;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      for (int i=0; i<edges[u].size(); i++) {
        int v = edges[u][i];
        int c = cap[u][i];
        if (dist[v] >= 0 || c == 0) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    
    return dist[t] >= 0;
  }
  
  int dfs(int u, int f) {
    if (u == t) return f;
    for (; it[u]<edges[u].size(); ++it[u]) {
      int i = it[u];
      int v = edges[u][i];
      int c = cap[u][i];
      if (dist[v] == dist[u] + 1 && c > 0) {
        int flow = dfs(v, min(f, c));
        if (flow > 0) {
          cap[u][i] -= flow;
          cap[v][rev[u][i]] += flow;
          return flow;
        }
      }
    }
    
    return 0;
  }
  
  int maxflow() {
    int ret = 0;
    while (bfs()) {
      for (int i=0; i<=t; i++) it[i] = 0;
      while (int flow = dfs(s, INF)) {
        ret += flow;
      }
    }
    
    return ret;
  }
} dinic;

void build() {  
  vector<int> workers(c, c + k);
  sort(workers.begin(), workers.end());

  dinic.s = 0;
  for (int i = 0; i < k; ) {
    int j = i;
    while (j < k && workers[j] == workers[i]) ++j;
    dinic.addEdge(dinic.s, i+1, j - i);
    i = j;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < b[i].size(); ++j) {
      if (binary_search(workers.begin(), workers.end(), b[i][j])) {

        int worker_idx = lower_bound(workers.begin(), workers.end(), b[i][j]) - workers.begin();

        dinic.addEdge(worker_idx + 1, i + k + 1, 1);
      }
    }
  }

  dfs(0, 0);

  int cycleNode = 1 + k + n;
  int nonCycleNode = 2 + k + n;
  int cycle_size = 0;
  dinic.t = k + n + 3;
  for (int i = 0; i < n; ++i) {
    if (cycle[i]) {
      dinic.addEdge(i + k + 1, cycleNode, 1);
      ++cycle_size;
    } else {
      dinic.addEdge(i + k + 1, nonCycleNode, 1);
    }
  }

  dinic.addEdge(cycleNode, dinic.t, cycle_size - 1);
  dinic.addEdge(nonCycleNode, dinic.t, n - cycle_size);
}

int main() {
  scanf("%d %d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    --a[i];

    edges[i].push_back(a[i]);
    edges[a[i]].push_back(i);

    int m;
    scanf("%d", &m);
    b[i].resize(m);
    for (int j = 0; j < m; ++j) {
      scanf("%d", &b[i][j]);
    }
  }

  for (int i = 0; i < k; ++i) scanf("%d", &c[i]);

  build();

  if (dinic.maxflow() != n-1) return 0 * printf("-1\n");

  vector<pair<int, int>> roads;
  for (int i = 0; i < n; ++i) {
    int node = i + k + 1;

    pair<int, int> road = {0, 0};
    for (int j = 0; j < dinic.edges[node].size(); ++j) {
      if (dinic.edges[node][j] >= n + k + 1 && dinic.cap[node][j] == 0) {
        road = {i+1, a[i]+1};
        break;
      } 
    }

    roads.emplace_back(road);
  }

  vector<pair<int, int>> workers;
  for (int i = 0; i < k; ++i) workers.emplace_back(c[i], i);
  sort(workers.begin(), workers.end());

  vector<pair<int, int>> ans(k);
  for (int i = 0; i < k; ++i) {
    int node = i + 1;

    pair<int, int> road = {0, 0};
    int cnt = 0;
    for (int j = 0; j < dinic.edges[node].size(); ++j) {
      if (dinic.edges[node][j] >= k + 1 && dinic.cap[node][j] == 0) {
        ans[workers[i + cnt++].second] = roads[dinic.edges[node][j] - k - 1];
        assert(workers[i].first == workers[i+cnt-1].first);
      } 
    }
  }

  for (int i = 0; i < k; ++i) {
    printf("%d %d\n", ans[i].first, ans[i].second);
  }
  return 0;
}
