#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int n;
pair<int, int> points[N];

long long cross(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
  return 1LL * (q.first - p.first) * (r.second - q.second) - 1LL * (q.second - p.second) * (r.first - q.first);
}

vector<int> convex() {
  sort(points, points + n);
  
  vector<int> st;
  
  for (int i=0; i<n; i++) {
    while (st.size() >= 2 && cross(points[st[st.size() - 2]], points[st.back()], points[i]) >= 0) st.pop_back();
    st.push_back(i);
  }
  
  vector<int> ret = st;
  st.clear();
  
  for (int i=0; i<n; i++) {
    while (st.size() >= 2 && cross(points[st[st.size() - 2]], points[st.back()], points[i]) <= 0) st.pop_back();
    st.push_back(i);
  }
  
  for (int i=(int) st.size()-2; i>0; i--) ret.push_back(st[i]);
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    points[i] = {x, y};
  }
  
  vector<int> conv = convex();
  
  long long ans = 0;
  for (int i=0; i<conv.size(); i++) {
    int k = i+1;
    for (int j=i+1; j<conv.size(); j++) {
      while (k + 1 < conv.size() && 
          cross(points[conv[i]], points[conv[j]], points[conv[k]]) >
          cross(points[conv[i]], points[conv[j]], points[conv[k+1]])) {
        ++k;
      }
      
      ans = min(ans, cross(points[conv[i]], points[conv[j]], points[conv[k]]));
    }
  }
  
  ans = -ans;
  
  if (ans % 2 == 0) printf("%lld.00000\n", ans / 2);
  else printf("%lld.50000\n", ans / 2);
  return 0;
}
