#include <bits/stdc++.h>
using namespace std;

// z[i] = longest characters starting from i which is also prefix of s
// z("aaabaab") = [0, 2, 1, 0, 2, 1, 0]
vector<int> z_function(string s) {

  int n = (int) s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

int main() {

  {
    // Count number of occurences of p in s.
    string s = "aaabaab", p = "aa";
    vector<int> z = z_function(p + "$" + s);
    int cnt = 0;
    for (int i=0; i<s.size(); i++) if (z[i + p.size() + 1] == p.size()) ++cnt;
  }
  
  {
    // Count number of distinct substring in a string
    string s = "aaabaab";
    int cnt = 0;
    string t = "";
    for (int i=0; i<s.size(); i++) {
      t = s[i] + t;
      cnt += (int) t.size() - max(z_function(t));
    }
  }
  
  return 0;
}
