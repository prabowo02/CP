#include <bits/stdc++.h>
using namespace std;

long long gcd(long long x, long long y) {
  while (y) {
    long long t = x;
    x = y;
    y = t % y;
  }
  return x;
}

pair<long long, int> Fraction(long long x, int y) {
  int d = gcd(x, y);
  return {x / d, y / d};
}

bool cmpFrac(pair<long long, int> p, pair<long long, int> q) {
  return p.first * q.second < q.first * p.second;
}

int solve(int n, int d, const vector<long long> &a) {
  map<pair<long long, int>, vector<int>> pizza;
  for (long long ang: a) {
    for (int i = 0; i < d; ++i) {
      pair<long long, int> f = Fraction(ang, i+1);
      pizza[f].push_back(i+1);
    }
  }

  int l = 0, r = (int) pizza.size() - 1;
  vector<pair<long long, int>> fracs;
  for (auto f: pizza) fracs.push_back(f.first);
  sort(fracs.begin(), fracs.end(), cmpFrac);

  while (l <= r) {
    int mid = (l + r) / 2;

    long long sum = 0;
    for (long long ang: a) sum += ang * fracs[mid].second / fracs[mid].first;
    if (sum >= d) {
      l = mid + 1;
    } else {
      r = mid - 1;
      fracs.resize(mid);
    }
  }

  int ans = d-1;
  for (pair<long long, int> frac: fracs) {
    int cnt = 0, cum = 0;
    sort(pizza[frac].begin(), pizza[frac].end());
    for (int s: pizza[frac]) {
      cnt += 1; cum += s;
      if (cum > d) {
        --cnt;
        break;
      }
    }

    ans = min(ans, d - cnt);
  }

  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    int n, d;
    scanf("%d %d", &n, &d);

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);

    printf("Case #%d: %d\n", tc+1, solve(n, d, a));
  }
  return 0;
}
