#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, m, k, s;
int p[N], q[N];

void read() {
  scanf("%d %d %d %d", &n, &m, &k, &s);

  int a, b, c, d;

  for (int i = 0; i < k; ++i) {
    scanf("%d", &p[i]);
  }
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    p[i] = (1LL * a * p[i-2] + 1LL * b * p[i-1] + c) % d + 1;
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d", &q[i]);
  }
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < m; ++i) {
    q[i] = (1LL * a * q[i-2] + 1LL * b * q[i-1] + c) % d + 1;
  }
}

bool check(long long x) {
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    int l = p[i], r = p[i], cnt = 0;
    while (cur < m && max(r, q[cur]) - min(l, q[cur]) + 
          min(max(r, q[cur]) - p[i], p[i] - min(l, q[cur])) + 1LL * (cnt+1) * s <= x) {
      l = min(l, q[cur]);
      r = max(r, q[cur]);
      ++cnt;
      ++cur;
    }
  }

  return cur == m;
}

int solve() {
  read();
  sort(p, p + n);
  sort(q, q + m);

  long long l = 1, r = 1e16, ans = -1;
  while (l <= r) {
    long long mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld\n", ans);
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
