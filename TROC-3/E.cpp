#include <bits/stdc++.h>
using namespace std;

const int N = 405;

int n, m, K;

int dp[2][N][N];

vector<int> a[100005];

int main() {
  scanf("%d %d %d", &n, &m, &K);
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      int tmp;
      scanf("%d", &tmp);
      a[i+j].push_back(tmp);
    }
  }
  
  int dj[4] = {0, 0, -1, -1};
  int dk[4] = {0, -1, 0, -1};
  int dj2[4] = {0, 0, 1, 1};
  int dk2[4] = {0, 1, 0, 1};
  
  dp[0][0][0] = 0;
  for (int i=1; i<n+m-1; i++) {
    int len = a[i].size();
    // cerr << len << endl;
    
    for (int j=0; j<len; j++) {
      for (int k=j; k<len; k++) {
        for (int l=0; l<4; l++) {
          
          int nj, nk;
          if (i < m) {
          nj = j + dj[l];
          nk = k + dk[l];
          } else {
            nj = j + dj2[l];
            nk = k + dk2[l];
          }
          
          if (nk < nj) swap(nj, nk);
          
          if (nj < 0 || nk >= a[i-1].size()) continue;
          
          if (j == k) {
            dp[i&1][j][k] = max(dp[i&1][j][k], dp[i+1&1][nj][nk] + a[i][j] + (a[i][k] ^ K));
          } else {
            dp[i&1][j][k] = max(dp[i&1][j][k], dp[i+1&1][nj][nk] + a[i][j] + a[i][k]);
          }
        }
      }
      // cerr << endl;
    }
  }
  
  printf("%d\n", dp[n+m-2&1][0][0]);
  
  return 0;
}
