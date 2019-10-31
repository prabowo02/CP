#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, l, r, k;
int a[N];

int ans[N];

int main() {
  scanf("%d %d %d %d", &n, &l, &r, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  ans[n-1] = l;
  for (int i = n-2; i >= 0; --i) {
    if (a[i] > a[i+1]) {
      ans[i] = ans[i+1] + 1;
    } else if (a[i] < a[i+1]) {
      ans[i] = max(l, ans[i+1] - k);
    } else {
      ans[i] = ans[i+1];
    }
  }

  if (ans[0] > r) return 0 * printf("-1\n");
  for (int i = 1; i < n; ++i) {
    if (a[i-1] < a[i]) {
      ans[i] = max(ans[i], ans[i-1] + 1);
    } else if (a[i-1] > a[i]) {
      ans[i] = max(ans[i], ans[i-1] - k);
    } else {
      ans[i] = max(ans[i-1], ans[i]);
    }

    if (ans[i] > r) return 0 * printf("-1\n");
  }

  for (int i = 0; i < n-1; ++i) {
    printf("%d ", ans[i]);
  }
  printf("%d\n", ans[n-1]);
  return 0;
}
