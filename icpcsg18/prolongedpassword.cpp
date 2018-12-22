#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

char s[N];
char t[26][55];
int len[26];

int nxt[55][26];
int go(int x, long long y) {
  while (y > 0) {
    int ctz = __builtin_ctzll(y);
    x = nxt[ctz][x];
    y -= 1LL << ctz;
  }
  
  return x;
}

long long memo[55][26];
long long expand(int x, long long k) {
  if (k == 0) return 1;
  if (memo[k][x] >= 0) return memo[k][x];
  
  long long ret = 0;
  for (int i=0; i<len[x]; i++) {
    ret += expand(t[x][i] - 'a', k-1);
  }
  
  return memo[k][x] = ret;
}

int main() {
  scanf("%s", s);
  for (int i=0; i<26; i++) {
    scanf("%s", t + i);
    len[i] = strlen(t[i]);
  }
  
  memset(memo, -1, sizeof memo);
  
  for (int i=0; i<26; i++) nxt[0][i] = t[i][0] - 'a';
  for (int i=1; i<55; i++) for (int j=0; j<26; j++) {
    nxt[i][j] = nxt[i-1][nxt[i-1][j]];
  }
  
  long long K;
  scanf("%lld", &K);
  
  int m;
  scanf("%d", &m);
  
  while (m--) {
    long long n;
    scanf("%lld", &n);
    
    long long k = K;
    
    char *ss = s;
    while (n > 1) {
      bool found = false;
      for (long long i=0; i<=k; i++) {
        int nc = go(ss[0] - 'a', k - i);
        if (expand(nc, i) >= n) {
          found = true;
          ss = t[nc];
          k = i - 1;
          break;
        }
      }
      
      if (!found) {
        n -= expand(ss[0] - 'a', k);
        ss = ss + 1;
      }
    }
    
    printf("%c\n", go(ss[0] - 'a', k) + 'a');
  }
  return 0;
}
