#include <bits/stdc++.h>
using namespace std;

const int N = 3003;
const int MOD = 1000000007;

int n;
string s[N];

int cnt[N][26];
int odd[N];

int dp[2][1 << 15];

int main() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    cin >> s[i];
  }
  
  for (int i=0; i<n; i++) {
    for (int j=0; j<s[i].size(); j++) {
      cnt[i][s[i][j] - 'a']++;
    }
    
    for (int j=0; j<='o'-'a'; j++) {
      if (cnt[i][j] & 1) odd[i] |= 1 << j;
    }
  }
  
  dp[0][0] = 1;
  for (int i=0; i<15; i++) dp[0][1 << i] = 1;
  
  for (int i=0; i<n; i++) {
    for (int j=0; j<1<<15; j++) dp[i+1&1][j] = (dp[i&1][j ^ odd[i]] + dp[i&1][j]) % MOD;
  }
  
  printf("%d\n", (dp[n&1][0] + MOD - 1) % MOD);
  
  return 0;
}
