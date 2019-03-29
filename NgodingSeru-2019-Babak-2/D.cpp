#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const long long INFLL = 1000000000000000000LL;

int n;
char s[N];

long long get(int i) {
  long long cur = 0;
  
  vector<int> emptyL, emptyR;
  for (int j=0; j<i; j++) if (s[j] == '-') emptyL.push_back(j);
  for (int j=n-1; j>=i; j--) if (s[j] == '-') emptyR.push_back(j);
  
  deque<int> pendingL, pendingR;
  
  int l = i-1, r = i;
  
  auto pindahKanan = [&]() {
    cur += emptyR.back() - l;
    
    if (emptyL.size() == 0 || l > emptyL.back()) emptyL.push_back(l);
    else pendingL.push_back(l);
    
    emptyR.pop_back();
    if (pendingR.size() > 0 && (emptyR.size() == 0 || emptyR.back() > pendingR.front())) {
      emptyR.push_back(pendingR.front());
      pendingR.pop_front();
    }
  };
  
  auto pindahKiri = [&]() {
    cur += r - emptyL.back();
    
    if (emptyR.size() == 0 || r < emptyR.back()) emptyR.push_back(r);
    else pendingR.push_back(r);
    
    emptyL.pop_back();
    if (pendingL.size() > 0 && (emptyL.size() == 0 || emptyL.back() < pendingL.front())) {
      emptyL.push_back(pendingL.front());
      pendingL.pop_front();
    }
  };
  
  while (l >= 0 && r < n) {
    while (l >= 0 && s[l] != 'K') --l;
    while (r < n && s[r] != 'B') ++r;

    if (l >= 0 && r < n) {
      if (emptyL.size() == 0) {
        pindahKanan();
        pindahKiri();
      } else if (emptyR.size() == 0) {
        pindahKiri();
        pindahKanan();
      } else if (emptyR.back() - l < r - emptyL.back()) {
        pindahKanan();
        pindahKiri();
      } else {
        pindahKiri();
        pindahKanan();
      }
      
      --l, ++r;
    }
  }
  
  while (l >= 0) {
    if (s[l] == 'K') {
      if (emptyR.size() == 0) {
        cur = INFLL;
        break;
      }
      
      pindahKanan();
    }
    
    --l;
  }
  
  while (r < n) {
    if (s[r] == 'B') {
      if (emptyL.size() == 0) {
        cur = INFLL;
        break;
      }
      
      pindahKiri();
    }
    
    ++r;
  }
  
  return cur;
}

int main() {
  scanf("%d", &n);
  scanf("%s", s);
    
  int cntB = 0, cntK = 0;
  for (int i=0; i<n; i++) {
    if (s[i] == 'B') ++cntB;
    if (s[i] == 'K') ++cntK;
  }
   
  int l = cntB, r = n - cntK;
  long long ans = INFLL;
  while (l < r) {
    int mid1 = l + r >> 1;
    int mid2 = mid1 + 1;
    
    long long a1 = get(mid1), a2 = get(mid2);
    
    if (a1 < a2) {
      r = mid2 - 1;
      ans = min(ans, a1);
    } else {
      l = mid1 + 1;
      ans = min(ans, a2);
    }
  }
  
  if (l == r) ans = min(ans, get(l));
  
  printf("%lld\n", ans);

  return 0;
}