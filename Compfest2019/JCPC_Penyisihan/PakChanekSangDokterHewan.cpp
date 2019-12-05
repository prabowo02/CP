#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 30;

int n, q;
int a[N];

struct SegTree {
  struct Node {
    int pre[2], suf[2], cnt;
    long long all;
    
    Node() {
      pre[0] = pre[1] = 0;
      suf[0] = suf[1] = 0;
      cnt = all = 0;
    }
    
    Node(int val) {
      // assert(val == 0 || val == 1);
      pre[val] = suf[val] = 1;
      pre[val^1] = suf[val^1] = 0;
      cnt = all = val;
    }
  };
  
  Node nodes[N << 2];
  
  Node merge(const Node &u, const Node &v) {
    Node ret;

    ret.pre[0] = u.pre[0] + (u.cnt & 1 ? v.pre[1] : v.pre[0]);
    ret.pre[1] = u.pre[1] + (u.cnt & 1 ? v.pre[0] : v.pre[1]);

    ret.suf[0] = v.suf[0] + (v.cnt & 1 ? u.suf[1] : u.suf[0]);
    ret.suf[1] = v.suf[1] + (v.cnt & 1 ? u.suf[0] : u.suf[1]);

    ret.all = u.all + v.all + 1LL * u.suf[0] * v.pre[1] + 1LL * u.suf[1] * v.pre[0];

    ret.cnt = u.cnt + v.cnt;

    return ret;
  }
  
  void build(int node, int l, int r, int a[]) {
    if (l == r) {
      nodes[node] = Node(a[l]);
      return;
    }
    
    int mid = l + r >> 1;
    build(node*2 + 1, l, mid+0, a);
    build(node*2 + 2, mid+1, r, a);
    nodes[node] = merge(nodes[node*2 + 1], nodes[node*2 + 2]);
  }

  void update(int node, int l, int r, int x, int val) {
    if (l > x || r < x) return;
    if (l == x && r == x) {
      nodes[node] = Node(val);
      return;
    }
    
    int mid = l + r >> 1;
    
    update(node*2 + 1, l, mid+0, x, val);
    update(node*2 + 2, mid+1, r, x, val);
    nodes[node] = merge(nodes[node*2 + 1], nodes[node*2 + 2]);
  }
  
  Node query(int node, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return Node();
    if (l >= ll && r <= rr) return nodes[node];
    
    int mid = l + r >> 1;
    
    return merge(query(node*2 + 1, l, mid+0, ll, rr),
                 query(node*2 + 2, mid+1, r, ll, rr));
  }
  
  void build(int a[]) {
    build(0, 0, n-1, a);
  }
  
  void update(int x, int v) {
    update(0, 0, n-1, x, v);
  }
  
  long long query(int l, int r) {
    return query(0, 0, n-1, l, r).all;
  }
} tree[LOG];

int b[N];
void build(int a[]) {
  for (int i = 0; i < LOG; ++i) {
    for (int j = 0; j < n; ++j) b[j] = a[j] >> i & 1;
    tree[i].build(b);
  }
}

void update(int x, int v) {
  for (int i = 0; i < LOG; ++i) {
    tree[i].update(x, v >> i & 1);
  }
}

long long query(int l, int r) {
  long long ret = 0;
  for (int i = 0; i < LOG; ++i) {
    ret += tree[i].query(l, r) * (1LL << i);
  }
  return ret;
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  
  build(a);
  
  while (q--) {
    int t, x, y;
    scanf("%d %d %d", &t, &x, &y);
    
    if (t == 1) update(--x, y);
    else if (t == 2) printf("%lld\n", query(--x, --y));
  }
  return 0;
}
