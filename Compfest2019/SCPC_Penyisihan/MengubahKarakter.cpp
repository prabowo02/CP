#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, m;
char s[N];

long long cnt[26];

int main() {
  scanf("%d %d", &n, &m);
  scanf("%s", s);

  for (int i = 0; i < n; ++i) {
    ++cnt[s[i] - 'A'];
  }

  for (int i = 0; i < m; ++i) {
    scanf("%s", s);
    int changed = cnt[s[0] - 'A'];
    cnt[s[0] - 'A'] = 0;

    scanf("%s", s);
    for (int j = 0; j < strlen(s); ++j) {
      cnt[s[j] - 'A'] += changed;
    }
  }

  long long ans = 0;
  for (int i = 0; i < 26; ++i) ans += cnt[i];
  printf("%lld\n", ans);
  return 0;
}
