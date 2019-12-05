#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k;
int a[N*2];

int getModeCount(int a[]) {
  sort(a, a + n*2);

  int ret = 1, cur = 1;
  for (int i = 1; i < n*2; ++i) {
    if (a[i-1] == a[i]) ret = max(ret, ++cur);
    else {
      ret = max(ret, cur = 1);
    }
  }

  return ret;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n*2; ++i) scanf("%d", a + i);

  printf(getModeCount(a) - n <= k ? "Ya\n" : "Tidak\n");
  return 0;
}
