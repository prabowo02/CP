#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;

vector<int> division[N];

int ans[N];

int main() {
  scanf("%d", &n);
  
  for (int i=0; i<n; i++) {
    int a;
    scanf("%d", &a);
    division[--a].push_back(i);
  }
  
  int maxi = 0;
  for (int i=1; i<n; i++) if (division[i].size() > division[maxi].size()) {
    maxi = i;
  }
  
  swap(division[0], division[maxi]);
  
  int idx = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<division[i].size(); j++) {
      ans[idx] = division[i][j] + 1;
      
      idx += 2;
      if (idx >= n) idx = 1;
    }
  }
  
  for (int i=0; i<n; i++) {
    printf("%d%c", ans[i], i == n-1 ? '\n' : ' ');
  }
  
  return 0;
}
