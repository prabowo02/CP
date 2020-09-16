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
  set<tuple<int, int, int>> rooms;

  int ans = 1;
  int th = 0, tw = 0;
  for (int i = 0; i < n; ++i) {
    int L = l[i], R = l[i] + w[i];
    pair<int, int> reinsertL = {-1, -1}, reinsertR = {-1, -1};
    while (true) {
      set<tuple<int, int, int>>::iterator it = rooms.upper_bound(make_tuple(R + 1, -1, -1));
      if (it == rooms.begin()) break;
      --it;

      int curL, curR, curH;
      tie(curL, curR, curH) = *it;

      if (curR < L) break;

      if (curL < L) reinsertL = {curL, curH};
      if (curR > R) reinsertR = {curR, curH};

      tw -= curR - curL;

      {
        auto nit = next(it);
        int nh = (nit != rooms.end() && get<0>(*nit) == curR ? get<2>(*nit) : 0);

        th = (th - max(0, curH - nh) + min(curH, nh)) % MOD;
        if (th < 0) th += MOD;
      }

      {
        int nh = (it != rooms.begin() && get<1>(*prev(it)) == curL ? get<2>(*prev(it)) : 0);

        th = (th - max(0, curH - nh) + min(curH, nh)) % MOD;
        if (th < 0) th += MOD; 
      }

      rooms.erase(it);
    }

    auto it = rooms.insert(make_tuple(L, R, h[i])).first;
    tw += R - L;
    th = (th + h[i]*2) % MOD;

    if (reinsertL.first != -1) {
      if (it != rooms.begin() && get<1>(*prev(it)) == reinsertL.first) {
        th = (th - min(get<2>(*prev(it)), reinsertL.second) * 2 + MOD) % MOD;
      }
      tw += L - reinsertL.first;
    }

    if (reinsertR.first != -1) {
      auto nit = next(it);
      if (nit != rooms.end() && get<0>(*nit) == reinsertR.first) {
        th = (th - min(get<2>(*nit), reinsertR.second) * 2 + MOD) % MOD;
      }
      tw += reinsertR.first - R;
    }

    if (reinsertL.first != -1) rooms.insert(make_tuple(reinsertL.first, L, reinsertL.second));
    if (reinsertR.first != -1) rooms.insert(make_tuple(R, reinsertR.first, reinsertR.second));

    ans = (2LL * tw + th) * ans % MOD;
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
