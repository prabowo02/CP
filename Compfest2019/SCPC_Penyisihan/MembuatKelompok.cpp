#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, k;
int a[N];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n*2; ++i) scanf("%d", a + i);

  sort(a, a + n*2);

  for (int i = 0; i < n*2; i += 2) if (a[i+1] - a[i] > k) {
    return 0 * printf("Tidak\n");
  }

  printf("Ya\n");
  return 0;
}
