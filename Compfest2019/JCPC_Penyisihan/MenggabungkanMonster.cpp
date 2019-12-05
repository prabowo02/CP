#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
long long a[N];

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%lld", a + i);
    a[i] += a[i-1];
  }

  long long ans = 0;
  for (int i = m+1; i <= n; ++i) {
    ans = max(ans, a[i] - a[i-m-1]);
  }

  printf("%lld\n", ans);
  return 0;
}
