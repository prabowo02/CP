#include <bits/stdc++.h>
using namespace std;

const int N = 40;

int n;
long long C[N][N];

void init() {
  C[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
  }
}

int solve() {
  scanf("%d", &n);

  vector<pair<int, int>> ans;
  int rgt = 1, frst = -1;
  for (int r = 30; r >= 0; --r) {
    if ((1LL << r) + r > n) {
      if (frst != -1) {
        if (rgt == 1) ans.push_back({r, r});
        else ans.push_back({r, 0});
        --n;
      }

      continue;
    }
    if (frst == -1) frst = r;

    if (rgt == 1) {
      for (int c = r; c >= 0; --c) ans.push_back({r, c});
    } else {
      for (int c = 0; c <= r; ++c) ans.push_back({r, c});
    }

    n -= 1LL << r;
    rgt *= -1;
  }

  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n; ++i) {
    ++frst;
    ans.push_back({frst, frst});
  }

  assert(ans.size() <= 500);
  for (pair<int, int> p: ans) {
    printf("%d %d\n", p.first + 1, p.second + 1);
  }
  return 0;
}

int main() {
  init();
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d:\n", tc+1);
    solve();
  }
  return 0;
}
