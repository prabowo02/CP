#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k;
pair<int, int> c[N], d[N];

int solve() {
  scanf("%d %d", &n, &k);
  for (int i=0; i<n; i++) {
    scanf("%d", &c[i].first);
    c[i].second = i;
  }
  
  for (int i=0; i<n; i++) {
    scanf("%d", &d[i].first);
    d[i].second = i;
  }
  
  sort(c, c + n, greater<pair<int, int>>());
  sort(d, d + n);
  
  set<int> usedC;
  set<int> okayD;
  set<int> nopeD;
  
  usedC.insert(-1);
  usedC.insert(n);
  
  // for maintaining C[i] - k <= D[i] <= C[i] + k
  okayD.insert(-1);
  okayD.insert(n);
  
  // for maintaining D[i] > C[i] + k
  nopeD.insert(-1);
  nopeD.insert(n);
  
  long long ans = 0;
  int lo = n, hi = n;
  for (int i=0; i<n; i++) {
    int pc = c[i].first;
    int idxc = c[i].second;
    
    auto itc = usedC.lower_bound(idxc);
    int Rc = *itc - 1;
    
    --itc;
    int Lc = *itc + 1;
    
    
    
    while (lo > 0 && d[lo-1].first + k >= pc) {
      okayD.insert(d[--lo].second);
    }
    
    while (hi > 0 && d[hi-1].first - k > pc) {
      okayD.erase(d[--hi].second);
      nopeD.insert(d[hi].second);
    }
    
    auto itd = nopeD.lower_bound(idxc);
    if (*itd == idxc) continue;
    
    Rc = min(Rc, *itd - 1);
    --itd;
    
    Lc = max(Lc, *itd + 1);
    
    itd = okayD.lower_bound(idxc);
    int Rd = *itd;
    int Ld;
    
    if (Rd == idxc) Ld = idxc;
    else {
      --itd;
      Ld = *itd;
    }
    
    
    ans += 1LL * (idxc - Lc + 1) * (Rc - idxc + 1);
    ans -= 1LL * (idxc - max(Lc, Ld + 1) + 1) * (min(Rc, Rd - 1) - idxc + 1);
    
    // cerr << idxc << ": " << Lc << " " << Rc << "; " << Ld << " " << Rd << " " << ans << endl;;
    usedC.insert(idxc);
  }
  
  printf("%lld\n", ans);
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tc=0; tc<t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
