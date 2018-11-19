#include <bits/stdc++.h>
using namespace std;

const int N = 2222;

int n, p, t, v, d;
int x[N], h[N];

int main() {
  scanf("%d %d %d %d %d", &n, &p, &t, &v, &d);
  for (int i=0; i<n; i++) scanf("%d", x + i);
  for (int i=0; i<n; i++) scanf("%d", h + i);
  
  vector<pair<int, int>> pos;
  for (int i=0; i<n; i++) {
    pos.push_back({x[i], h[i]});
    pos.push_back({x[i] + p, -h[i]});
  }
  
  sort(pos.begin(), pos.end());
  
  multiset<int> ms;
  ms.insert(t);
  long long ans = 0;
  for (int i=0; i<pos.size(); i++) {
    if (i > 0) {
      ans += 1LL * (pos[i].first - pos[i-1].first) * (t - *ms.begin()) * d;
    }
    if (pos[i].second < 0) {
      ms.erase(ms.find(-pos[i].second));
    } else ms.insert(pos[i].second);
    
  }
  
  printf("%.8lf\n", (double) ans / v);
  return 0;
}