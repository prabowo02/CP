#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int MOD = 1000000007;

int n, k, w;
int l[N], h[N];

void read() {
  scanf("%d %d %d", &n, &k, &w);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &l[i]);
  }
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    l[i] = (1LL * a * l[i-2] + 1LL * b * l[i-1] + c) % d + 1;
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

  int ans = 1;
  vector<int> heights;
  int lst = -10;
  int th = 0, peri = 0;
  for (int i = 0; i < n; ++i) {
    if (l[i] > lst + (int) heights.size()) {
      peri = (peri + 2 * heights.size() + th) % MOD;
      lst = l[i];
      th = 0;
      heights.clear();
    }

    for (int j = l[i] - lst; j < l[i] - lst + w; ++j) {
      if (j == heights.size()) heights.push_back(0);
      if (h[i] > heights[j]) {
        int addH = heights[j];
        addH = max(addH, max(j > 0 ? heights[j-1] : 0, j + 1 < heights.size() ? heights[j+1] : 0));
        addH = max(0, h[i] - addH);
        th = (th + addH * 2) % MOD;
        heights[j] = h[i];
      }
      // cerr << heights.size() << endl;
    }

    ans = 1LL * ans * (peri + th + heights.size() * 2) % MOD;
    // cerr << th + heights.size() * 2 << endl;
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
