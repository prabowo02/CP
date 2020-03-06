void bfs(int u, int dist[]) {
  for (int i = 0; i < n; ++i) dist[i] = -1;
 
  queue<int> q;
  q.push(u);
  dist[u] = 0;
 
  while (q.size()) {
    int u = q.front();
    q.pop();
 
    for (int v: edges[u]) {
      if (dist[v] != -1) continue;
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
}

void dijkstra(int u, int dist[]) {
  for (int i = 0; i < n; ++i) dist[i] = -1;
 
  priority_queue<pair<int, int>> pq;
  pq.push(u);
  dist[u] = 0;
 
  while (pq.size()) {
    int u = pq.top().first;
    int d = -pq.top().second;
    pq.pop();

    if (dist[u] != -1) continue;
    dist[u] = d;
 
    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i];
      int w = weights[u][i];
      if (dist[v] != -1) continue;

      pq.push({v, -d - w});
    }
  }
}
