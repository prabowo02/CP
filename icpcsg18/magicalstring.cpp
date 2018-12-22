#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int INF = 1000000000;

char s[N];

vector<pair<int, int>> build_initial_intervals(char s[]) {
  int n = strlen(s);
  vector<pair<int, int>> intervals;

  for (int i=0; i<n; i++) {
    int r = i+1;
    if (i < n-1) {
      while (r+1 < n && s[r+1] == s[i+1]) ++r;
    }
    
    int l = i-1;
    if (i > 0) {
      while (l-1 >= 0 && s[l-1] == s[i-1]) --l;
    }
    
    if (i > 0 && i < n-1 && s[i-1] == s[i+1] && s[i] != s[i+1]) {
      intervals.push_back({l, r});
    } else {
      if (i < n-1 && s[i] != s[i+1] && r - i + 1 >= 3) {
        intervals.push_back({i, r});
      }
      
      if (i > 0 && s[i] != s[i-1] && i - l + 1 >= 3) {
        intervals.push_back({l, i});
      }
    }
  }
  
  return intervals;
}

void extend_intervals(vector<pair<int, int>> &intervals) {
  int sz = intervals.size();
  for (int i=0; i<sz; i++) {
    int l = max(i-10, 0);
    int r = min(i+10, sz-1);
    for (int j=l; j<=r; j++) {
      if (intervals[i].second < intervals[j].second && intervals[i].second >= intervals[j].first && intervals[j].second - intervals[i].second >= 3) {
        intervals.push_back({intervals[i].second + 1, intervals[j].second});
      }
      
      if (intervals[i].first > intervals[j].first && intervals[i].first <= intervals[j].second && intervals[i].first - intervals[j].first >= 3) {
        intervals.push_back({intervals[j].first, intervals[i].first - 1});
      }
    }
    
    if (intervals[i].second - intervals[i].first + 1 == 5) {
      for (int j=l; j<=r; j++) for (int k=l; k<=r; k++) {
        if (intervals[j].second == intervals[i].first && intervals[k].first == intervals[i].second) {
          intervals.push_back({intervals[i].first + 1, intervals[i].second - 1});
        }
      }
    }
  }
}

int dp[N][N * 10];
int interval_selection(vector<pair<int, int>> intervals, int k) {
  int n = intervals.size();
  
  sort(intervals.begin(), intervals.end());
  intervals.resize(unique(intervals.begin(), intervals.end()) - intervals.begin());
  
  int nxt[n];
  for (int i=0; i<n; i++) {
    nxt[i] = lower_bound(intervals.begin(), intervals.end(), intervals[i].second + 1, [](pair<int, int> p, int q) {
      return p.first < q;
    }) - intervals.begin();
  }
  
  int len[n];
  for (int i=0; i<n; i++) {
    len[i] = intervals[i].second - intervals[i].first + 1;
  }
  
  for (int i=0; i<=n; i++) dp[0][i] = 0;
  for (int i=1; i<=k; i++) dp[i][n] = 0;
  
  for (int i=1; i<=k; i++) {
    for (int j=n-1; j>=0; j--) {
      dp[i][j] = max(
        dp[i][j+1],
        dp[i-1][nxt[j]] + len[j]
      );
    }
  }
  
  return dp[k][0];
}

int solve() {
  int k, n;
  scanf("%s %d", s, &k);
  
  vector<pair<int, int>> intervals = build_initial_intervals(s);
  
  // for (pair<int, int> p: intervals) cerr << p.first << " " << p.second << endl; cerr << "===========\n";
  
  extend_intervals(intervals);
 
  // for (pair<int, int> p: intervals) cerr << p.first << " " << p.second << endl; cerr << "===========\n";
  
  printf("%d\n", interval_selection(intervals, k));
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) solve();
  return 0;
}
