#include <bits/stdc++.h>
using namespace std;

const int N = 20002;
const long long INF = 1000000000000000000LL;

int n;
int C[4][N];
int W[4][N];
int S[4], T[4];

int main() {
  scanf("%d", &n);
  for (int i=0; i<4; i++) {
    for (int j=0; j<n; j++) scanf("%d", &C[i][j]);
    for (int j=0; j<n; j++) scanf("%d", &W[i][j]);
  }
  
  for (int i=0; i<4; i++) {
    scanf("%d %d", S + i, T + i);
    --S[i], --T[i];
  }
  
  int miniST[4]; long long sumST[4]; int lenST[4];
  int maxLen = 0;
  for (int i=0; i<4; i++) {
    miniST[i] = C[i][T[i]];
    sumST[i] = 0;
    
    if (S[i] <= T[i]) {
      maxLen = max(maxLen, lenST[i] = T[i] - S[i]);
      
      for (int j=S[i]; j<T[i]; j++) {
        sumST[i] += W[i][j];
        miniST[i] = min(miniST[i], C[i][j]);
      }
    } else {
      maxLen = max(maxLen, lenST[i] = n - S[i] + T[i]);
      
      for (int j=S[i]; j<n; j++) {
        sumST[i] += W[i][j];
        miniST[i] = min(miniST[i], C[i][j]);
      }
      
      for (int j=0; j<T[i]; j++) {
        sumST[i] += W[i][j];
        miniST[i] = min(miniST[i], C[i][j]);
      }
    }
  }
  
  int miniAll[4]; long long sumAll[4];
  for (int i=0; i<4; i++) {
    sumAll[i] = 0;
    miniAll[i] = 2000000;
    for (int j=0; j<n; j++) {
      sumAll[i] += W[i][j];
      miniAll[i] = min(miniAll[i], C[i][j]);
    }
  }
  
  long long ans = INF;
  for (int i=maxLen; i<=2000000; i++) {
    long long sum = 0;
    for (int j=0; j<4; j++) {
      long long tmp1 = INF, tmp2 = INF, tmp3 = INF;
      
      tmp1 = 1LL * miniST[j] * (i - lenST[j]) + sumST[j];
      
      if (i >= lenST[j] + n) {
        tmp2 = 1LL * miniAll[j] * (i - lenST[j] - n) + sumAll[j] + sumST[j];
        
        tmp3 = 1LL * miniAll[j] * ((i - lenST[j]) % n) + 1LL * sumAll[j] * ((i - lenST[j]) / n) + sumST[j];
      }
      
   // err << tmp1 << " " << tmp2 << " " << tmp3 << endl;
      sum += min(tmp1, min(tmp2, tmp3));
    }
    
    
    ans = min(ans, sum);
  }
  
  printf("%lld\n", ans);
  return 0;
}