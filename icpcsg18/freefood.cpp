#include <bits/stdc++.h>
using namespace std;

int n;
bool food[400];

int main() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    int s, t;
    scanf("%d %d", &s, &t);
    for (int j=s; j<=t; j++) food[j] = true;
  }
  
  int ans = 0;
  for (int i=0; i<400; i++) if (food[i]) ans += 1;
  printf("%d\n", ans);
  return 0;
}
