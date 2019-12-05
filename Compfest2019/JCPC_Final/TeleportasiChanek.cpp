#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, k;
vector<int> edges[N];
vector<int> weights[N];
vector<int> teleportersInCity[N];
vector<int> teleporters[N];
int p[N];

void read() {
  scanf("%d %d %d", &n, &m, &k);

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;

    assert(w == 1);

    edges[u].push_back(v);
    weights[u].push_back(w);

    edges[v].push_back(u);
    weights[v].push_back(w);
  }

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);

    int c;
    for (int j = 0; j < t; ++j) {
      scanf("%d", &c);
      --c;

      teleportersInCity[i].push_back(c);
      teleporters[c].push_back(i);
    }
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d", p + i);

    assert(p[i] == 1);
  }
}

bool vis[N];
bool teleporterUsed[N];
long long dijkstra() {
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
  pq.push({0LL, 0});

  while (pq.size()) {
    long long d = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (u == n-1) return d;

    if (vis[u]) continue;
    vis[u] = true;

    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i];
      int w = weights[u][i];

      pq.push({d + w, v});
    }

    for (int teleporter: teleportersInCity[u]) {
      if (teleporterUsed[teleporter]) continue;
      teleporterUsed[teleporter] = true;

      for (int v: teleporters[teleporter]) {
        pq.push({d + p[teleporter], v});
      }
    }
  }

  return -1;
}

int dist[N];
int bfs() {
  queue<int> q;
  q.push(0);
  dist[0] = 0;
  vis[0] = true;

  while (q.size()) {
    int u = q.front();
    q.pop();

    if (u == n-1) return dist[n-1];

    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i];

      if (vis[v]) continue;
      vis[v] = true;
      dist[v] = dist[u] + 1;

      q.push(v);
    }

    for (int teleporter: teleportersInCity[u]) {
      if (teleporterUsed[teleporter]) continue;
      teleporterUsed[teleporter] = true;

      for (int v: teleporters[teleporter]) {
        if (vis[v]) continue;
        vis[v] = true;
        dist[v] = dist[u] + 1;

        q.push(v);
      }
    }
  }

  return -1;
}

int main() {
  read();  
  printf("%d\n", bfs());
  return 0;
}