#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k;
int t[N], r[N], c[N], V[N];

map<pair<int, int>, int> pos;
vector<int> row_green[N*10], row[N*10];
vector<int> col_blue[N*10], col[N*10];

int idx[N];
vector<int> uidx;

vector<int> edges[N], redges[N];;
bool vis[N];

void dfs(int u, vector<int> &order, vector<int> edges[]) {
  vis[u] = true;
  for (int v: edges[u]) {
    if (vis[v]) continue;
    dfs(v, order, edges);
  }
  
  order.push_back(u);
}

vector<int> scc() {
  vector<int> order;
  for (int i: uidx) if (!vis[i]) dfs(i, order, edges);
  
  reverse(order.begin(), order.end());
  
  memset(vis, false, sizeof vis);
  
  vector<int> v;
  for (int u: order) {
    if (vis[u]) continue;
    
    vector<int> comp;
    dfs(u, comp, redges);
    
    // cerr << "c: "; for (int c: comp) cerr << c << " "; cerr << endl;
    
    int maxi = 0;
    for (int v: comp) maxi = max(maxi, V[v]);
    v.push_back(maxi);
  }
  
  return v;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i=0; i<n; i++) {
    scanf("%d %d %d %d", t + i, r + i, c + i, V + i);
    --r[i], --c[i];
    
    pos[{r[i], c[i]}] = i;
    
    if (t[i] == 2) {
      row_green[r[i]].push_back(i);
    } else {
      row[r[i]].push_back(i);
    }
    
    if (t[i] == 3) {
      col_blue[c[i]].push_back(i);
    } else {
      col[c[i]].push_back(i);
    }
    
    idx[i] = i;
  }
  
  for (int i=0; i<N*10; i++) {
    if (row_green[i].size() > 0) {
      int maxi = row_green[i][0];
      for (int u: row_green[i]) {
        if (V[u] > V[maxi]) maxi = u;
      }
      
      for (int u: row_green[i]) {
        idx[u] = maxi;
      }
    }
    
    if (col_blue[i].size() > 0) {
      int maxi = col_blue[i][0];
      for (int u: col_blue[i]) {
        if (V[u] > V[maxi]) maxi = u;
      }
      
      for (int u: col_blue[i]) {
        idx[u] = maxi;
      }
    }
  }
  
  for (int i=0; i<n; i++) uidx.push_back(idx[i]);
  sort(uidx.begin(), uidx.end());
  uidx.resize(unique(uidx.begin(), uidx.end()) - uidx.begin());
  
  int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
  int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
  for (int i=0; i<n; i++) {
    if (i != idx[i]) continue;
    
    if (t[i] == 1) {
      for (int j=0; j<8; j++) {
        int nx = r[i] + dx[j];
        int ny = c[i] + dy[j];
        
        if (pos.find({nx, ny}) != pos.end()) {
          int u = idx[pos[{nx, ny}]];
          edges[u].push_back(i);
          redges[i].push_back(u);
        }
      }
    }
    
    if (t[i] == 2) {
      for (int uu: row[r[i]]) {
        edges[idx[uu]].push_back(i);
        redges[i].push_back(idx[uu]);
      }
    }
    
    if (t[i] == 3) {
      for (int uu: col[c[i]]) {
        edges[idx[uu]].push_back(i);
        redges[i].push_back(idx[uu]);
      }
    }
  }
  
  long long ans = 0;
  vector<int> v = scc();
  sort(v.begin(), v.end(), greater<int>());
  k = min(k, (int) v.size());
  
  for (int i=0; i<k; i++) ans += v[i];
  
  printf("%lld\n", ans);
  return 0;
}
