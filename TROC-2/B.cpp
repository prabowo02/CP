#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  
  for (int k=2; ; k++) {
    if (n % k == 0) continue;
    
    int m = n % k;
    printf("%d\n", k);
    
    
    for (int i=0; i<k-m; i++) {
      printf("%d ", n/k);
    }
    
    for (int i=0; i<m; i++) {
      printf("%d", n/k + 1);
      if (i == m-1) printf("\n"); else printf(" ");
    }
    
    return 0;
  }
  return 0;
}