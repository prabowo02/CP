/**
 * Let dp[i][j] = Number of string of length (j-i) with exactly i zeros with no m-consecutive 1.
 * It is easy to see that dp[0][i] = (dp[0][i-1] + dp[0][i-2] + ... + dp[0][i-m]) * (c-2), with dp[0][i] = (c-1)^i for i < m.
 * To simplify the base case, use dp[0][-1] = 1/(c-2) and dp[0][i] = 0 for i < -1.
 * It can be shown that
 * dp[i][j] = dp[i-1][j]*dp[0][0] + dp[i-1][j-1]*dp[0][1] + ... + dp[i-1][0]*dp[0][j]
 * Although this looks like a convolution, we can apply the recurrence of dp[0][i] to the transition of dp[i][j].
 * So, dp[i][j] = dp[i-1][j] * (dp[0][-1] + ... + dp[0][-m]) + ... + dp[i-1][0] * (dp[0][j-1] + ... + dp[0][j-m])
 * After that, we expand and reorder:
 * dp[i][j] = dp[i-1][j] * dp[0][-1] + dp[i-1][j-1] * dp[0][0] + ... + dp[i-1][0] * dp[0][k-1] + 
 *            dp[i-1][j] * dp[0][-2] + dp[i-1][j-1] * dp[0][-1] + ... + dp[i-1][0] * dp[0][k-2] + 
 *            ... +
 *            dp[i-1][j] * dp[0][-m] + dp[i-1][j-1] * dp[0][-m+1] + ... + dp[i-1][0] * dp[0][k-m]
 *
 * Applying the recurrence of the dp, we get:
 * dp[i][j] = dp[i-1][j] + dp[i][j-1] * (c-2) + 
 *            dp[i-1][j-1] + dp[i][j-2] * (c-2) +
 *            ... + 
 *            dp[i-1][j-m+1] + dp[i][j-m] * (c-2)
 * 
 * Now, computing the dp can be done easily by maintaining the sum of m previous terms. 
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000005;
const int MOD = 1000000007;

int L, N, m; long long c;

// Number of strings of length i with no m-consecutive.
long long dp[MAXN];

// For flying table.
long long table[2][MAXN];

int main() {
  scanf("%d %d %d %lld", &L, &N, &m, &c);
  c %= MOD;  
  
  dp[0] = 1; long long sum = 1;
  for (int i=1; i<m; i++) sum += dp[i] = dp[i-1] * (c-1) % MOD;
  sum %= MOD;
  for (int i=m; i<=L; i++) {
      dp[i] = sum * (c-2) % MOD;
      sum += dp[i] - dp[i-m];
      sum %= MOD;
      if (sum < 0) sum += MOD;
  }
  
  for (int i=0; i<=L; i++) table[0][i] = dp[i];  
  
  sum = 0;
  for (int i=0; i<=L; i++) sum += dp[i];
  sum %= MOD;
  
  long long ans = (sum-1) * N % MOD;
  for (int n=1; n<=N; n++) {
    sum = 0;
    long long psum = 0;
    long long pdegsum = 0;
    for (int l=0; l<=L-n; l++) {
      pdegsum += table[n+1&1][l];
      if (l >= m) pdegsum -= table[n+1&1][l-m];
      pdegsum %= MOD;
      
      sum += table[n&1][l] = (pdegsum + psum * (c-2)) % MOD;
      
      psum += table[n&1][l];
      if (l >= m) psum -= table[n&1][l-m];
      psum %= MOD;
    }      
    
    sum %= MOD;
    ans += sum * (N-n+1) % MOD;
  }
  
  ans %= MOD;
  if (ans < 0) ans += MOD;
  
  printf("%lld\n", ans);
  return 0;
}
