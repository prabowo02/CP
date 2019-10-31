#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
int r[N], c[N];

int preR[N], preC[N];

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &r[i]);
    preR[i+1] = preR[i] + (r[i] & 1);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    preC[i+1] = preC[i] + (c[i] & 1);
  }

  while (q--) {
    int x, y, xx, yy;
    scanf("%d %d %d %d", &x, &y, &xx, &yy);
    if (xx < x) swap(x, xx);
    if (yy < y) swap(y, yy);

    if (preR[xx] - preR[x-1] > 0 && preR[xx] - preR[x-1] < xx-x+1) {
      printf("NO\n");
      continue;
    }
    if (preC[yy] - preC[y-1] > 0 && preC[yy] - preC[y-1] < yy-y+1) {
      printf("NO\n");
      continue;
    }

    printf("YES\n");
  }
  return 0;
}
