#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
int p[N];

int sum[N];

int main() {
  scanf("%d %d", &n, &q);
  for (int i=0; i<n; i++) {
    scanf("%d", p + i);
    sum[i+1] = (sum[i] ^ p[i]);
  }
  
  while (q--) {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    int r = min(c, d), l = max(a, b);
    printf("%d\n", l <= r ? sum[r] ^ sum[l - 1] : 0);
  }

  return 0;
}
