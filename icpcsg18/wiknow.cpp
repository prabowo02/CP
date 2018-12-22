#include <bits/stdc++.h>
using namespace std;

const int N = 400004;

int n;
int a[N];

int input() {
  char c = getchar_unlocked();
  
  int ret = 0;
  while (c >= '0' && c <= '9') {
    ret = ret*10 + c - '0';
    c = getchar_unlocked();
  }
  
  return ret;
}

struct SegTree {
 private:
  int mini[N << 2];
 
  void build(int node, int l, int r) {
    if (l == r) {
      mini[node] = 1000000000;
      return;
    }
    
    int mid = l + r >> 1;
    
    build(node*2 + 1, l, mid+0);
    build(node*2 + 2, mid+1, r);
    mini[node] = 1000000000;
  }
  
  void update(int node, int l, int r, int x, int val) {
    if (l > x || r < x) return;
    if (l == x && r == x) {
      mini[node] = val;
      return;
    }
    
    int mid = l + r >> 1;
    
    update(node*2 + 1, l, mid+0, x, val);
    update(node*2 + 2, mid+1, r, x, val);
    mini[node] = min(mini[node*2 + 1], mini[node*2 + 2]);
  }
  
  int query(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return 1000000000;
    if (l >= a && r <= b) return mini[node];
    
    int mid = l + r >> 1;
    
    return min(query(node*2 + 1, l, mid, a, b), query(node*2 + 2, mid+1, r, a, b));
  }
  
 public:
  void build(int n) {
    build(0, 1, n);
  }
  
  void update(int x, int val) {
    update(0, 1, n, x, val);
  }
  
  int query(int l, int r) {
    return query(0, 1, n, l, r);
  }
} tree;

int fi[N], lst[N], prv[N];

int main() {
  n = input();
  for (int i=1; i<=n; i++) {
    a[i] = input();
  }
  
  for (int i=1; i<=n; i++) {
    if (lst[a[i]] == 0) fi[a[i]] = i;
    prv[i] = lst[a[i]];
    lst[a[i]] = i;
  }
  
  tree.build(n);
  
  pair<int, int> ans = {n+1, n+1};
  for (int i=n; i>=0; i--) {
    int tmp = tree.query(fi[a[i]] + 1, i - 1);
    if (tmp <= n) ans = min(ans, {a[i], tmp});
    tree.update(prv[i], a[i]);
  }
  
  if (ans.first == n+1) printf("-1\n");
  else printf("%d %d\n", ans.first, ans.second);
  return 0;
}
