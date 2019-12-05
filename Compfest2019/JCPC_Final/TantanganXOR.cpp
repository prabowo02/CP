#include <bits/stdc++.h>
using namespace std;

const int N = 22;

int n, q;
long long a[N];
vector<int> masks;

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < q; ++i) {
    int u, v;
    long long x;
    scanf("%d %d %lld", &u, &v, &x);
    --u, --v;

    a[u] ^= x; a[v] ^= x;
  }

  for (int mask = 1; mask < 1<<n; ++mask) {
    long long op = 0;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) op ^= a[i];
    }

    if (op == 0) masks.push_back(mask);
  }

  stable_sort(masks.begin(), masks.end(), [](int x, int y) {
    return __builtin_popcount(x) < __builtin_popcount(y);
  });

  int cur = 0, ans = 0;
  for (int mask: masks) {
    if ((cur & mask) == 0) {
      cur |= mask;
      ans += __builtin_popcount(mask) - 1;
    }
  }

  printf("%d\n", ans);

  return 0;
}