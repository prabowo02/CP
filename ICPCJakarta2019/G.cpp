#include <bits/stdc++.h>
using namespace std;

const int M = 100005;

int m, n;
int a[M];
vector<int> b[M];

int performance[M];

struct SegTree {
  int mini[M << 2];
  int lazy[M << 2];

  void propagate(int node) {
    lazy[node*2 + 1] += lazy[node];
    mini[node*2 + 1] += lazy[node];
    lazy[node*2 + 2] += lazy[node];
    mini[node*2 + 2] += lazy[node];

    lazy[node] = 0;
  }

  void build(int node, int l, int r, int perf[]) {
    if (l == r) {
      mini[node] = perf[l];
      return;
    }

    int mid = l + r >> 1;

    build(node*2 + 1, l, mid+0, perf);
    build(node*2 + 2, mid+1, r, perf);
    mini[node] = min(mini[node*2 + 1], mini[node*2 + 2]);
  }

  void update(int node, int l, int r, int a, int b, int val) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      lazy[node] += val;
      mini[node] += val;
      return;
    }

    int mid = l + r >> 1;
    propagate(node);

    update(node*2 + 1, l, mid+0, a, b, val);
    update(node*2 + 2, mid+1, r, a, b, val);
    mini[node] = min(mini[node*2 + 1], mini[node*2 + 2]);
  }

  void build(int perf[]) {
    build(0, 0, m-1, perf);
  }

  int query() {
    return mini[0];
  }

  void update(int x, int val) {
    update(0, 0, m-1, x+1, m-1, val);
  }
} tree;

int main() {
  int q;
  scanf("%d %d %d", &n, &m, &q);

  int randall;
  scanf("%d", &randall);
  int perf = 0;

  for (int i = 1; i < n; ++i) {
    scanf("%d", &a[i]);
    perf += a[i] < randall;
  }

  for (int i = 0; i < m; ++i) {
    int r;
    scanf("%d", &r);
    b[i].resize(r);

    performance[i] = perf -= r;

    for (int j = 0; j < r; ++j) {
      scanf("%d", &b[i][j]);
      perf += b[i][j] < randall;
    }
  }

  tree.build(performance);

  while (q--) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    --x, --y;

    if (b[x][y] < randall && z > randall) tree.update(x, -1);
    else if (b[x][y] > randall && z < randall) tree.update(x, 1);

    b[x][y] = z;

    printf("%d\n", tree.query() < 0 ? 0 : 1);
  }

  return 0;
}
