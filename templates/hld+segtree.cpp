/** 

HLD + Segment Tree
0-based index

This example handles: 
- Path update xor with 1, 
- Path query {sum, length}

**/

#include <bits/stdc++.h>
using namespace std;

const int N = 250005;

int n, m;
vector<int> edges[N];

struct SegTree {
  int cnt[N << 2];
  int lazy[N << 2];
  
  SegTree() {
    for (int i=0; i<N<<2; i++) cnt[i] = lazy[i] = 0;
  }
  
  void update_node(int node, int l, int r) {
    /** Adjust this function **/
    
    lazy[node] ^= 1;
    cnt[node] = r - l + 1 - cnt[node];
  }
  
  void propagate(int node, int l, int r) {
    if (lazy[node] == 0) return;
    
    int mid = l + r >> 1;
    
    update_node(node*2 + 1, l, mid+0);
    update_node(node*2 + 2, mid+1, r);
    
    /** Adjust this line **/
    lazy[node] ^= 1;
  }
  
  void update(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      update_node(node, l, r);
      return;
    }
    
    propagate(node, l, r);
    
    int mid = l + r >> 1;
    
    update(node*2 + 1, l, mid+0, a, b);
    update(node*2 + 2, mid+1, r, a, b);
    
    /** Adjust this line **/
    cnt[node] = cnt[node*2 + 1] + cnt[node*2 + 2];
  }
  
  int query(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return cnt[node];
    
    propagate(node, l, r);
    
    int mid = l + r >> 1;
    
    /** Adjust this line **/
    return query(node*2 + 1, l, mid, a, b) + query(node*2 + 2, mid+1, r, a, b);
  }
  
  void update(int l, int r) {
    update(0, 0, n-1, l, r);
  }
  
  int query(int l, int r) {
    return query(0, 0, n-1, l, r);
  }
};

struct HLD {
  SegTree tree;
  
  int heavy[N], head[N], cnt[N], depth[N], idx[N], par[N];
  
  void dfs(int u, int p) {
    par[u] = p; 
    heavy[u] = -1;
    cnt[u] = 1;
    
    for (int v: edges[u]) {
      if (v == p) continue;
      depth[v] = depth[u] + 1;
      
      dfs(v, u);
      
      cnt[u] += cnt[v];
      if (heavy[u] == -1 || cnt[v] > cnt[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
  
  void build() {
    depth[0] = 0;
    dfs(0, 0);
    
    int cur = 0;
    for (int i=0; i<n; i++) {
      if (i == 0 || heavy[par[i]] != i) {      
        for (int j=i; j!=-1; j=heavy[j]) {
          head[j] = i;
          idx[j] = cur++;
        }
      }
    }
  }
  
  pair<int, int> query(int u, int v) {
    
    pair<int, int> ret = {0, 0};
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]]) swap(u, v);
      
      /** Start adjust here **/
      ret.first += tree.query(idx[head[u]], idx[u]);
      ret.second += depth[u] - depth[head[u]] + 1;
      tree.update(idx[head[u]], idx[u]);
      /** End adjust here **/
      
      u = par[head[u]];
    }
    
    if (depth[u] < depth[v]) swap(u, v);
    
    /** Start adjust here **/
    ret.first += tree.query(idx[v]+1, idx[u]);
    ret.second += depth[u] - depth[v];
    tree.update(idx[v]+1, idx[u]);
    /** End adjust here **/
    
    return ret;
  }
} hld;

int main() {
  scanf("%d", &n);
  
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  
  hld.build();
  
  scanf("%d", &m);
  while (m--) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    
    hld.query(u, v);
  }
  return 0;
}
