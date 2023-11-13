#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
vector<int> edges[N], redges[N];
bool vis[N];

void dfs(int u, vector<int> &order, vector<int> edges[]) {
  vis[u] = true;
  for (int v: edges[u]) {
    if (vis[v]) continue;
    dfs(v, order, edges);
  }
  
  order.push_back(u);
}

vector<vector<int>> scc() {
  vector<int> order;
  for (int i: uidx) if (!vis[i]) dfs(i, order, edges);
  
  reverse(order.begin(), order.end());
  
  memset(vis, false, sizeof vis);
  
  vector<vector<int>> ret;
  for (int u: order) {
    if (vis[u]) continue;
    
    vector<int> comp;
    dfs(u, comp, redges);
    
    ret.push_back(comp);
  }
  
  return ret;
}

void read() {
  scanf("%d %d", &n, &m);
  for (int i=0; i<m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    
    edges[u].push_back(v);
    redges[v].push_back(u);
  }
}

int main() {

  return 0;
}
