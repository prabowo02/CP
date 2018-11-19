#include <bits/stdc++.h>
using namespace std;

int x, a[3];

int main() {
  scanf("%d %d %d %d", &x, a, a + 1, a + 2);
  
  sort(a, a + 3);
  
  int ans = 0;
  for (int i=0; i<=10000; i++) {
    long long sum = 1LL * i * (a[0] + a[1] + a[2]);
    
    if (sum <= x) ans = i*3;
    if (sum + a[0] <= x) ans = i*3 + 1;
    if (sum + a[0] + a[1] <= x) ans = i*3 + 2;
  }
  
  printf("%d\n", ans);
  return 0;
}
