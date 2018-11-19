#include <bits/stdc++.h>
using namespace std;

int n, x, y, c, d, m1, m2;

void f(int x, int c, int m, int count[]) {
  for (int i=0; i<m; i++) count[i] = 0;
  vector<int> vis(m, -1);
  
  vector<int> v;
  for (int i=0; i<n; i++) {
    if (vis[x] >= 0) {
      int len = (int) v.size() - vis[x];
      
      for (int j=vis[x]; j<v.size(); j++) {
        count[v[j]] += (n - i) / len + ( j-vis[x] < (n-i) % len );
      }
      return;
    }
    
    ++count[x];
    v.push_back(x);
    vis[x] = i;
    x = 1LL * x * c % m;
  }
  
}

int count1[55555], count2[55555];

int main() {
  scanf("%d %d %d %d %d %d %d", &n, &x, &y, &c, &d, &m1, &m2);

  f(x, c, m1, count1);
  f(y, d, m2, count2);
  
  long long ans = 0;
  
  int j = m2-1;
  for (int i=m1-1; i>=0; i--) {
    while (j > 0 && count2[j] < count1[i]) {
      ans += 1LL * count2[j] * i * j;
      count1[i] -= count2[j];
      --j;
    }
    
    ans += 1LL * count1[i] * i * j;
    count2[j] -= count1[i];
  }
  
  printf("%lld\n", ans);
  
  return 0;
}