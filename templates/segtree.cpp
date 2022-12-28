#include <bits/stdc++.h>
using namespace std;

class SegTree {
  int n;
  vector<int> lazy;
  vector<int> value;

  int base = -1;
  inline int op(int a, int b) { return max(a, b); }

  // int base = 0;
  // inline int op(int a, int b) { return a + b; }

  // int base = 2e9;
  // inline int op(int a, int b) { return min(a, b); }

  void build(int idx, int l, int r, const vector<int> &vals) {
    if (l + 1 == r) {
      value[idx] = vals[l];
      return;
    }
    int mid = (l + r) / 2;
    int lnode = idx + 1;
    int rnode = idx + (mid - l) * 2;
    build(lnode, l, mid, vals);
    build(rnode, mid, r, vals);
    value[idx] = op(value[lnode], value[rnode]);
  }
  
  void propagate(int idx, int l, int r) {
    int mid = (l + r) / 2;
    int lnode = idx + 1;
    int rnode = idx + (mid - l) * 2;

    lazy[lnode] = op(lazy[lnode], lazy[idx]);
    lazy[rnode] = op(lazy[rnode], lazy[idx]);
    value[lnode] = op(value[lnode], lazy[idx]);
    value[rnode] = op(value[rnode], lazy[idx]);

    lazy[idx] = base;
  }
  
  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (l >= rr || r <= ll) return;
    if (l >= ll && r <= rr) {
      lazy[idx] = op(lazy[idx], val);
      value[idx] = op(value[idx], val);
      return;
    }
    
    propagate(idx, l, r);
    
    int mid = (l + r) / 2;
    int lnode = idx + 1;
    int rnode = idx + (mid - l) * 2;

    update(lnode, l, mid, ll, rr, val);
    update(rnode, mid, r, ll, rr, val);

    value[idx] = op(value[lnode], value[rnode]);
  }
  
  int query(int idx, int l, int r, int ll, int rr) {
    if (l >= rr || r <= ll) return base;
    if (l >= ll && r <= rr) return value[idx];
    
    propagate(idx, l, r);
    
    int mid = (l + r) / 2;
    int lnode = idx + 1;
    int rnode = idx + (mid - l) * 2;
    
    return op(query(lnode, l, mid, ll, rr), query(rnode, mid, r, ll, rr));
  }

 public:
  void build(const vector<int> &vals) {
    n = vals.size();
    lazy.assign(n * 2, base);
    value.resize(n * 2);
    build(0, 0, n, vals);
  }

  void build(int _n) {
    n = _n;
    lazy.assign(n * 2, base);
    value.assign(n * 2, base);
  }

  inline void update(int x, int val) { update(0, 0, n, x, x + 1, val); }
  inline void update(int l, int r, int val) { update(0, 0, n, l, r, val); }
  inline int query(int x) { return query(0, 0, n, x, x + 1); }
  inline int query(int l, int r) { return query(0, 0, n, l, r); }
} tree;

int solve() {
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    solve();
  }  
  return 0;
}