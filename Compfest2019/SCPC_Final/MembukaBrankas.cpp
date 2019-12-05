#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
char a[N], b[N];

int solve() {
  scanf("%d", &n);
  scanf("%s", a);
  scanf("%s", b);

  multiset<pair<char, char>> pairs;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      pairs.insert({a[i], b[i]});
    }
  }

  int ans = 0;
  while (pairs.size() > 0) {
    char c = pairs.begin()->first;
    char d = pairs.begin()->second;

    ++ans;
    if (pairs.count({d, c}) > 0) {
      pairs.erase(pairs.find({c, d}));
      pairs.erase(pairs.find({d, c}));
    } else {
      pairs.erase(pairs.begin());
    }
  }

  printf("%d\n", ans);
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) solve();
}
