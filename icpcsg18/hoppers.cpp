#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, m;
vector<int> edges[N];

int color[N];
bool isBipartite(int u) {
  queue<int> q;
  q.push(u);
  color[u] = 1;
  
  bool ret = true;
  while (q.size()) {
    int u = q.front();
    q.pop();
    
    for (int v: edges[u]) {
      if (color[v] > 0) {
        if (color[v] != 3 - color[u]) ret = false;
        continue;
      }
      
      color[v] = 3 - color[u];
      q.push(v);
    }
  }
  
  return ret;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i=0; i<m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  
  bool hasNonBipartite = false;
  int ans = 0;
  for (int i=0; i<n; i++) {
    if (color[i] > 0) continue;
    if (!isBipartite(i)) hasNonBipartite = true;
    ++ans;
  }
  
  if (hasNonBipartite) --ans;
  
  printf("%d\n", ans);
  return 0;
}
