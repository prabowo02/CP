#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int n;
char I[N];
char O[N];

char ans[N][N];

int solve() {
  scanf("%d", &n);
  scanf("%s", I);
  scanf("%s", O);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ans[i][j] = 'N';
    }
    ans[i][n] = 0;
  }

  for (int i = 0; i < n; ++i) {
    int j = i + 1;
    ans[i][i] = 'Y';
    for (int j = i + 1; j < n && O[j-1] == 'Y' && I[j] == 'Y'; ++j) {
      ans[i][j] = 'Y';
    }
    for (int j = i - 1; j >= 0 && O[j+1] == 'Y' && I[j] == 'Y'; --j) {
      ans[i][j] = 'Y';
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%s\n", ans[i]);
  }

  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: \n", tc+1);
    solve();
  }
  return 0;
}
