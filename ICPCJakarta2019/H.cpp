#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];
pair<int, int> lands[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &lands[i].first, &lands[i].second);
    if (lands[i].second < lands[i].first) swap(lands[i].first, lands[i].second);
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) ans = max(ans, 1LL * lands[i].first * lands[i].second);
  
  sort(lands, lands + n, greater<pair<int, int>>());
  int maks = lands[0].second;
  for (int i = 1; i < n; ++i) {
    ans = max(ans, 2LL * lands[i].first * min(maks, lands[i].second));
    maks = max(maks, lands[i].second);
  }

  printf("%lld", ans >> 1);
  if (ans & 1) printf(".5"); else printf(".0");
  printf("\n");
  return 0;
}
