#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int L[N], R[N];

int main() {
  scanf("%d", &n);
  
  vector<pair<int, int>> v;
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", L + i, R + i);
    
    v.emplace_back(L[i], 1);
    v.emplace_back(R[i] + 1, -1);
  }
  
  sort(v.begin(), v.end());
  
  int cur = 0, lst = -1;
  long long ans = 0;
  for (pair<int, int> p: v) {
    if (cur != 0) ans += 1LL * (p.first - lst) * (p.first + lst - 1) / 2;

    cur += p.second;
    lst = p.first;
  }
  
  printf("%lld\n", ans);
  return 0;
}
