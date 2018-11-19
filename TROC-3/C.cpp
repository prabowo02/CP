#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
int a[N];

set<int> num[N];

int ans[N];

int main() {
  scanf("%d %d", &n, &m);
  for (int i=0; i<n; i++) {
    scanf("%d", a + i);
  }
  
  for (int i=0; i<n; i++) {
    num[(i+1) % m].insert(i+1);
  }
  
  for (int i=0; i<n; i++) {
    if (num[a[i]].size() == 0) return 0 * printf("-1\n");
    
    ans[i] = *num[a[i]].rbegin();
    num[a[i]].erase(ans[i]);
  }
  
  for (int i=0; i<n; i++) {
    printf("%d", ans[i]);
    if (i == n-1) printf("\n");
    else printf(" ");
  }
  return 0;
}
