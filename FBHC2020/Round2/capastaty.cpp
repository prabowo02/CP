#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, k;
int s[N], x[N], y[N];

void readArray(int k, int n, int arr[]) {
  for (int i = 0; i < k; ++i) {
    scanf("%d", &arr[i]);
  }

  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  for (int i = k; i < n; ++i) {
    arr[i] = (1LL * arr[i-2] * a + 1LL * arr[i-1] * b + c) % d;
  }
}

void read() {
  scanf("%d %d", &n, &k);
  readArray(k, n, s);
  readArray(k, n, x);
  readArray(k, n, y);
}

int solve() {
  read();

  long long overflow = 0, underflow = 0, extraspace = 0, extraperson = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] < x[i]) {
      underflow += x[i] - s[i];
      extraspace += y[i];
    } else if (s[i] > x[i] + y[i]) {
      overflow += s[i] - (x[i] + y[i]);
      extraperson += y[i];
    } else {
      extraspace += x[i] + y[i] - s[i];
      extraperson += s[i] - x[i];
    }
  }

  if (overflow > underflow) {
    if (overflow > underflow + extraspace) printf("-1\n");
    else printf("%lld\n", overflow);
  } else if (overflow < underflow) {
    if (underflow > overflow + extraperson) printf("-1\n");
    else printf("%lld\n", underflow);
  } else {
    printf("%lld\n", overflow);
  }

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
