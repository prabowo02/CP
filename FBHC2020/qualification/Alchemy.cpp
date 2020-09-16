#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
char s[N];

int solve() {
  scanf("%d", &n);
  scanf("%s", s);

  int cnt[2] = {0, 0};
  for (int i = 0; i < n; ++i) {
    ++cnt[s[i] - 'A'];
  }

  if (abs(cnt[0] - cnt[1]) == 1) printf("Y\n");
  else printf("N\n");
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
