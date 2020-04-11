#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int S = 105;

int n;
char s[N][S];

int pre[N], suf[N];


int solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }

  string preStr = "";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; ; ++j) {
      if (s[i][j] == '*') {
        pre[i] = j + 1;
        break;
      }
      if (j < preStr.size() && preStr[j] != s[i][j]) {
        return 0 * printf("*\n");
      }
      if (j >= preStr.size()) {
        preStr += s[i][j];
      }
    }
  }

  string sufStr = "";
  for (int i = 0; i < n; ++i) {
    int len = strlen(s[i]);
    for (int j = len - 1; ; --j) {
      if (s[i][j] == '*') {
        suf[i] = j - 1;
        break;
      }
      if (len-j-1 < sufStr.size() && sufStr[len-j-1] != s[i][j]) {
        return 0 * printf("*\n");
      }
      if (len-j-1 >= sufStr.size()) {
        sufStr += s[i][j];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = pre[i]; j <= suf[i]; ++j) {
      if (s[i][j] == '*') continue;
      preStr += s[i][j];
    }
  }

  reverse(sufStr.begin(), sufStr.end());
  printf("%s\n", (preStr + sufStr).c_str());
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
