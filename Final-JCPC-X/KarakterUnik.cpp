#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
char s[N];

int len[N];

int bit[N];

void update(int x, int val) {
  for (int i=x+1; i<=n; i+=i&-i) bit[i-1] += val;
}

int query(int x) {
  int ret = 0;
  for (int i=x+1; i>0; i-=i&-i) ret += bit[i-1];
  return ret;
}

void updatelen(int i) {
  int mask = 0;
  for (int j=0; j<26; j++) {
    if (i - j < 0) break;
    
    int c = s[i-j] - 'a';
    
    if (mask >> c & 1) break;
    mask |= 1 << c;
  }
  
  int prvlen = len[i];
  len[i] = __builtin_popcount(mask);
  update(i, len[i] - prvlen);
}

int main() {
  scanf("%d %d", &n, &q);
  scanf("%s", s);
  
  for (int i=0; i<n; i++) {
    updatelen(i);
  }
  
  while (q--) {
    int t;
    scanf("%d", &t);
    
    if (t == 1) {
      int x; char c;
      scanf("%d %c", &x, &c);
      --x;
      
      s[x] = c;
      
      for (int i=x; i<x+26 && i<n; i++) {
        updatelen(i);
      }
    } else if (t == 2) {
      int l, r;
      scanf("%d %d", &l, &r);
      --l, --r;
      
      int ans = 0;
      for (int i=l; i<l+26 && i<=r; i++) ans += min(len[i], i-l+1);
      if (l+26 <= r) ans += query(r) - query(l+26 - 1);
      
      printf("%d\n", ans);
    }
  }

  return 0;
}
