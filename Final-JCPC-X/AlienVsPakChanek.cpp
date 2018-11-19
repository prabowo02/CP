#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, x;
int a[N][N];

long long sum[N][N];
long long get(int x, int y, int z) {
  return sum[x+z][y+z] - sum[x][y+z] - sum[x+z][y] + sum[x][y];
}

int main() {
  scanf("%d %d", &n, &x);
  for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
    scanf("%d", &a[i][j]);
    
    sum[i+1][j+1] = sum[i][j+1] + sum[i+1][j] - sum[i][j] + a[i][j];
  }

  long long ans = 0;
  for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
    int l = 1, r = n - max(i, j);
    
    while (l <= r) {
      int mid = l + r >> 1;
      
      if (get(i, j, mid) <= x) {
        ans = max(ans, get(i, j, mid));
        l = mid + 1;
      } else r = mid - 1;
    }
  }
  
  printf("%lld\n", ans);
  return 0;
}
