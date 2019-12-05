#include <bits/stdc++.h>
using namespace std;

const int LN = 18;
const int N = 200005;

int n, q;
vector<int> edges[N];
vector<int> weights[N];

bool vis[N];
priority_queue<int, vector<int>, greater<int>> queries[N];

long long ans[N];

void dfs(int u, int p) {
  vector<int> nodes;
  for (int i = 0; i < edges[u].size(); ++i) {
    int v = edges[u][i];
    int w = weights[u][i];
    
    if (v == p) continue;
    
    dfs(v, u);
    
    if (queries[v].size() > 0) {
      ans[queries[v].top()] += w;
    }
    
    if (queries[u].size() < queries[v].size()) swap(queries[u], queries[v]);
    
    while (queries[v].size()) {
      queries[u].push(queries[v].top());
      queries[v].pop();
    }
  }
  
  while (queries[u].size() >= 2) {
    int a = queries[u].top(); queries[u].pop();
    int b = queries[u].top();
    
    if (a == b) {
      queries[u].pop();
    } else {
      queries[u].push(a);
      break;
    }
  }
}

int main() {
  scanf("%d %d", &n, &q);
  
  int u, v, w;
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
    
    edges[u].push_back(v);
    weights[u].push_back(w);
    
    edges[v].push_back(u);
    weights[v].push_back(w);
  }
  
  for (int i = 0; i < q; ++i) {
    scanf("%d %d", &u, &v);
    --u, --v;
    
    if (u != v) {
      queries[u].push(i);
      queries[v].push(i);
    }
  }
  
  dfs(0, 0);
  
  for (int i = 0; i < q; ++i) printf("%lld\n", ans[i]);
  return 0;
}
