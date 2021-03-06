#include <bits/stdc++.h>
using namespace std;

const int N = 85000;
const int INF = 1000000000;

int n, k;


struct Dinic {
  int s, t;
  vector<int> edges[N], cap[N], rev[N];
  int dist[N], it[N];
  
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

int main() {

  scanf("%d %d", &n, &k);
  
  dinic.s = 0;
  for (int i=0; i<n; i++) dinic.addEdge(dinic.s, i+1, 1);
  
  int tim = n;
  for (int i=0; i<k; i++) {
    int m;
    scanf("%d", &m);
    
    int peserta;
    for (int j=0; j<m; j++) {
      tim++;
      for (int kk=0; kk<3; kk++) {
        scanf("%d", &peserta);
        dinic.addEdge(peserta, tim, 1);
      }
    }
  }
  
  dinic.t = tim + 1;
  for (int i=n+1; i<=tim; i++) dinic.addEdge(i, dinic.t, 1);
  
  printf("%d\n", dinic.maxflow());
  return 0;
}
