#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
const int INF = 1000000000;

struct MinCostFlow {
	struct Edge {
		int to, cap, flow, rev;
		int cost;
	};
	
	int source, sink;
	vector<Edge> edge[N];
	int pot[N];
	
	void addEdge (int u, int v, int c, int f) {
		Edge edge1 = {v, f, 0, (int) edge[v].size(), c};
		Edge edge2 = {u, 0, 0, (int) edge[u].size(), -c};
		edge[u].push_back (edge1);
		edge[v].push_back (edge2);
	}
	
	pair<int, int> dijkstra () {
    // pq{cost, flow}
		priority_queue<pair<int, int>> pq;
		pq.push (make_pair(0, source));
		
		bool vis[N] = {};
		int dist[N];
		for (int i=0; i<N; i++) dist[i] = INF;
		pair<int, int> prev[N];
		
		dist[source] = 0;
		
		while (pq.size()) {
			pair<int, int> now = pq.top();
			int u = now.second;
			pq.pop();
			
			if (vis[u]) continue;
			vis[u] = 1;
			
			for (int i=0; i<edge[u].size(); i++) {
				Edge e = edge[u][i];
				int v = e.to;
				// printf ("%d %d %d\n", v, e.cap, e.flow);
				
				if (e.cap - e.flow == 0) continue;
				
				int d = dist[u] + e.cost + pot[u] - pot[v];
				if (d < dist[v]) {
					dist[v] = d;
					pq.push (std :: make_pair (-d, v));
					prev[v] = std :: make_pair (u, i);
				}
			}
		}
		
		for (int i=0; i<N; i++) pot[i] += dist[i];
		
		if (dist[sink] == INF) return make_pair(0, 0);
		// printf ("%.5lf\n", dist[sink]);
		
		int f = INF;
		int sum = 0;
		int now = sink;
		
		while (now ^ source) {
			int u = prev[now].first;
			int i = prev[now].second;
			f = min(f, edge[u][i].cap - edge[u][i].flow);
			sum += edge[u][i].cost;
			now = u;
		}
		
		now = sink;
		while (now ^ source) {
			int u = prev[now].first;
			int i = prev[now].second;
			edge[u][i].flow += f;
			edge[now][edge[u][i].rev].flow -= f;
			now = u;
		}
		
		return std :: make_pair (f, sum * f);
	};
	
  // {flow, cost}
	pair<int, int> minCostMaxFlow () {
		pair<int, int> tmp = dijkstra();
		pair<int, int> ret = make_pair (0, 0);
		while (tmp.first) {
			ret.first += tmp.first;
			ret.second += tmp.second;
			tmp = dijkstra();
		}
		
		return ret;
	}
	
};

int main() {

  return 0;
}
