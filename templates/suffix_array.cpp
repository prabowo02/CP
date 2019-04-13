#include <bits/stdc++.h>
using namespace std;

vector<int> suffixArray(string &s) {
  int n = s.size();
  vector<int> sa(n), rank(n);
  iota(sa.begin(), sa.end(), 0);
  reverse(sa.begin(), sa.end());
  
  stable_sort(sa.begin(), sa.end(), [&s](int x, int y) {return s[x] < s[y];});
  for (int i=0; i<n; i++) rank[i] = s[i];
  
  for (int k=1; k<n; k<<=1) {
    vector<int> trank = rank;
    for (int i=0; i<n; i++) 
      rank[sa[i]] = (i > 0 && trank[sa[i-1]] == trank[sa[i]] && sa[i-1] + k < n && trank[sa[i-1] + (k>>1)] == trank[sa[i] + (k>>1)] ? rank[sa[i-1]] : i);
     
    vector<int> cnt(n), tsa = sa;
    iota(cnt.begin(), cnt.end(), 0);    
    
    for (int i=0; i<n; i++) {      
      if (tsa[i] - k >= 0)
        sa[cnt[rank[tsa[i] - k]]++] = tsa[i] - k;
    } 
  }
  
  return sa;
}

vector<int> LCP(string &s, vector<int> &sa) {
  int n = s.size();
  vector<int> rank(n);
  for (int i=0; i<n; i++) rank[sa[i]] = i;
  
  vector<int> lcp(n-1);
  for (int i=0, h=0; i<n; i++) {
    if (rank[i] < n-1) {
      for (int j=sa[rank[i] + 1]; max(i, j) + h < n && s[i+h] == s[j+h]; ++h);
      lcp[rank[i]] = h;
      if (h > 0) --h;
    }
  }
  return lcp;
}

int main() {
  string s = "banana$";
  vector<int> sa = suffixArray(s);
  vector<int> lcp = LCP(s, sa);
  
  return 0;
}