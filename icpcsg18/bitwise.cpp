#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, k;
int a[N];

bool can(int mask) {
  for (int st=30; st>=0; --st) {
    if (mask >> st & 1); else continue;
    
    int i, pre = 0, cur = 0;
    for (i=0; i<n; i++) {
      pre |= a[i];
      if (a[i] >> st & 1) {
        ++i;
        break;
      }
    }
    
    int cnt = 0;
    
    for (; i<n; i++) {
      cur |= a[i];
      if ((mask & cur) == mask) {
        ++cnt;
        cur = 0;
      }
    }
    
    if (((pre | cur) & mask) == mask) {
      ++cnt;
    }
    
    if (cnt >= k) return true;
  }
  
  int cnt = 0, cur = 0;
  for (int i=0; i<n; i++) {
    cur |= a[i];
    if ((mask & cur) == mask) {
      ++cnt;
      cur = 0;
    }
  }
  
  if (cnt >= k) return true;
  
  return false;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i=0; i<n; i++) {
    scanf("%d", a + i);
  }
  
  int ans = 0;
  for (int i=30; i>=0; i--) {
    if (can(ans | 1 << i)) {
      ans |= 1 << i;
    }
  }
  
  printf("%d\n", ans);
  
  return 0;
}
