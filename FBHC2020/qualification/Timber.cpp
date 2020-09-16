#include <bits/stdc++.h>
using namespace std;

const int N = 800005;

int n;
pair<int, int> trees[N];

map<int, int> lft, rgt;

int solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &trees[i].first, &trees[i].second);
  }
  sort(trees, trees + n);

  int ans = 0;

  rgt.clear();
  for (int i = 0; i < n; ++i) {
    int r = trees[i].first + trees[i].second;
    ans = max(ans, rgt[r] = max(rgt[r], rgt[trees[i].first] + trees[i].second));
  }

  lft.clear();
  for (int i = n-1; i >= 0; --i) {
    int l = trees[i].first - trees[i].second;
    ans = max(ans, lft[l] = max(lft[l], lft[trees[i].first] + trees[i].second));
  }

  for (pair<int, int> p: lft) {
    ans = max(ans, p.second + rgt[p.first]);
  }

  printf("%d\n", ans);
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
