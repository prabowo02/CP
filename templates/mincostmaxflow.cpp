#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
const int INF = 1000000000;

using Flow = int;
using Cost = int;
struct MinCostFlow {
  struct Edge {
    int to, rev;
    Flow cap, flow;
    Cost cost;
  };

  int source, sink;
  vector<Edge> edge[N];
  Cost pot[N];

  void reset() {
    for (int i = 0; i < N; ++i) {
      edge[i].clear();
      pot[i] = 0;
    }
  }

  void addEdge(int u, int v, Cost c, Flow f) {
    Edge edge1 = {v, (int) edge[v].size(), f, 0, c};
    Edge edge2 = {u, (int) edge[u].size(), 0, 0, -c};
    edge[u].push_back(edge1);
    edge[v].push_back(edge2);
  }

  pair<Flow, Cost> dijkstra() {
    priority_queue<pair<Cost, int>> pq;
    pq.push(make_pair(0, source));

    vector<bool> vis(sink + 1, false);
    vector<Cost> dist(sink + 1, INF);
    vector<pair<int, int>> prev(sink + 1);

    dist[source] = 0;

    while (pq.size()) {
      pair<Cost, int> now = pq.top();
      int u = now.second;
      pq.pop();

      if (vis[u]) continue;
      vis[u] = 1;

      for (int i = 0; i < edge[u].size(); ++i) {
        Edge e = edge[u][i];
        int v = e.to;

        if (e.cap - e.flow == 0) continue;

        Cost d = dist[u] + e.cost + pot[u] - pot[v];
        if (d < dist[v]) {
          dist[v] = d;
          pq.push(make_pair(-d, v));
          prev[v] = make_pair(u, i);
        }
      }
    }

    for (int i = 0; i <= sink; ++i) pot[i] += dist[i];

    if (dist[sink] == INF) return make_pair(0, 0);

    Flow f = INF;
    Cost sum = 0;
    int now = sink;

    while (now != source) {
      int u = prev[now].first;
      int i = prev[now].second;
      f = min(f, edge[u][i].cap - edge[u][i].flow);
      sum += edge[u][i].cost;
      now = u;
    }

    now = sink;
    while (now != source) {
      int u = prev[now].first;
      int i = prev[now].second;
      edge[u][i].flow += f;
      edge[now][edge[u][i].rev].flow -= f;
      now = u;
    }

    return make_pair(f, sum * f);
  };

  pair<Flow, Cost> minCostMaxFlow() {
    pair<Flow, Cost> tmp = dijkstra();
    pair<Flow, Cost> ret = make_pair(0, 0);
    while (tmp.first) {
      ret.first += tmp.first;
      ret.second += tmp.second;
      tmp = dijkstra();
    }
    return ret;
  }
} mcmf;

int main() {
  mcmf.sink = 1; mcmf.source = 0;
  mcmf.addEdge(0, 1, 1, 100);
  pair<int, int> = mcmf.minCostMaxFlow();
  return 0;
}
