#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n;
char a[N];

bool check(int x) {
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == '0') {
      cur = min(cur + x, x);
    } else if (a[i] == '1') {
      if (--cur < -x) return false;
    }
  }

  return cur >= 0;
}

int main() {
  scanf("%d", &n);
  scanf("%s", a);

  int l = 1, r = n, ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;

    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  printf("%d\n", ans);
  return 0;
}
