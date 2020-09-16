#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int MOD = 1000000007;

int n, k;
int l[N], h[N], w[N];

void read() {
  scanf("%d %d", &n, &k);

  int a, b, c, d;

  for (int i = 0; i < k; ++i) {
    scanf("%d", &l[i]);
  }
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    l[i] = (1LL * a * l[i-2] + 1LL * b * l[i-1] + c) % d + 1;
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d", &w[i]);
  }
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    w[i] = (1LL * a * w[i-2] + 1LL * b * w[i-1] + c) % d + 1;
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d", &h[i]);
  }
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    h[i] = (1LL * a * h[i-2] + 1LL * b * h[i-1] + c) % d + 1;
  }
}

int solve() {
  read();

  // L, R, H
  set<pair<int, int>> rooms;

  int ans = 1;
  int th = 0, tw = 0;
  for (int i = 0; i < n; ++i) {
    int L = l[i], R = l[i] + w[i];
    int merged = 0;
    while (true) {
      set<pair<int, int>>::iterator it = rooms.upper_bound(make_pair(R + 1, -1));
      if (it == rooms.begin()) break;
      --it;

      int curL, curR;
      tie(curL, curR) = *it;

      if (curR < L) break;

      ++merged;

      L = min(L, curL);
      R = max(R, curR);

      tw -= curR - curL;

      rooms.erase(it);
    }

    th = (th - 1LL * (merged-1) * h[i]) % MOD;
    if (th < 0) th += MOD;

    rooms.insert(make_pair(L, R));
    tw += R - L;

    ans = 2LL * (th + tw) * ans % MOD;
  }

  printf("%d\n", ans);
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
