#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MOD = 1000000007;

int n, m;
int a[N];

int pressed[N];

int main() {
  scanf("%d %d", &n, &m);
  
  int cnt = m;
  for (int i=0; i<m; i++) {
    scanf("%d", a + i);
    if (a[i] == 0) {
      --cnt;
    } else {
      pressed[a[i]] = 1;
    }
  }
  
  long long ans = 1;
  for (int i=1; i<=n; i++) {
    if (pressed[i]) {
      --cnt;
    } else {
      ans = ans * cnt % MOD;
    }
  }
  
  printf("%lld\n", ans);
  return 0;
}