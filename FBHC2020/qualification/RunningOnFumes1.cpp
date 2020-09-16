#include <bits/stdc++.h>
using namespace std;

const int N = 2000005;

int n, m;
int c[N];

pair<int, long long> dq[N];

int solve() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    if (c[i] == 0) --c[i];
  }
  c[0] = 0;

  int front = 0, tail = 0;
  dq[tail++] = {n-1, 0LL};

  for (int i = n-2; i >= 0; --i) {
    if (c[i] < 0) continue;
    while (front < tail && i + m < dq[front].first) ++front;
    if (front == tail) return 0 * printf("-1\n");

    long long cost = c[i] + dq[front].second;
    while (front < tail && dq[tail-1].second >= cost) --tail;
    assert(tail >= 0);
    dq[tail++] = {i, cost};
  }

  assert(tail >= 0);
  printf("%lld\n", dq[tail-1].second);
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
