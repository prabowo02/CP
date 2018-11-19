#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, m;
int a[N];
int b[N];
int c;

int main() {
  scanf("%d %d", &n, &m);
  
  printf("? %d %d\n", 1, 1);
  fflush(stdout);
  scanf("%d", &c);
  
  a[0] = c;
  for (int i=1; i<n; i++) {
    printf("? %d %d\n", i+1, 1);
    fflush(stdout);
    
    scanf("%d", a + i);
  }
  
  b[0] = c;
  for (int i=1; i<m; i++) {
    printf("? %d %d\n", 1, i+1);
    fflush(stdout);
    
    scanf("%d", b + i);
  }
  
  long long ans = 0;
  for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
    ans += (c ^ a[i] ^ b[j]);
  }
  
  printf("! %lld\n", ans);
  fflush(stdout);
  
  return 0;
}
