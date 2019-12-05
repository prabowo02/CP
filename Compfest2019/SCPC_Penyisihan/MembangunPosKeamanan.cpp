#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
vector<int> adj[N];

bool vis[N];
int bfs(int u) {
  queue<int> q;
  q.push(u);
  vis[u] = true;

  int ret = 0;
  while (q.size()) {
    int u = q.front();
    q.pop();

    ++ret;
    for (int v: adj[u]) {
      if (vis[v]) continue;
      vis[v] = true;
      q.push(v);
    }
  }

  return ret;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;
  for (int u = 0; u < n; ++u) {
    if (vis[u]) continue;
    ans += bfs(u) >> 1;
  }
  printf("%d\n", ans);
  return 0;
}