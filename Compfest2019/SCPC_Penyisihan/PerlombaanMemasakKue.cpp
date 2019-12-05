#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
vector<pair<int, int>> juries;
vector<pair<int, int>> cakes;

int ans[N];

long long cross(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
  return 1LL * (q.first - p.first) * (r.second - q.second) - 1LL * (q.second - p.second) * (r.first - q.first);
}

long long dot(pair<int, int> p, pair<int, int> q) {
  return 1LL * p.first * q.first + 1LL * p.second * q.second;
}

vector<pair<int, int>> upper_hull(vector<pair<int, int>> points) {
  sort(points.begin(), points.end());

  vector<pair<int, int>> upper;
  for (pair<int, int> point: points) {
    while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), point) > 0) upper.pop_back();
    upper.push_back(point);
  }

  reverse(upper.begin(), upper.end());

  return upper;
}

int main() {
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    juries.emplace_back(x, y);
  }

  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    cakes.emplace_back(x, y);
  }

  vector<pair<int, int>> upper_cake = upper_hull(cakes);
  vector<int> winning_cake(upper_cake.size() + 1);

  sort(juries.begin(), juries.end(), [](pair<int, int> p, pair<int, int> q) {
    return cross({0, 0}, p, q) > 0;
  });

  int l = 0, r = 0;
  for (pair<int, int> jury: juries) {
    while (l + 1 < upper_cake.size() && dot(jury, upper_cake[l]) < dot(jury, upper_cake[l+1])) ++l;
    while (r + 1 < upper_cake.size() && dot(jury, upper_cake[r]) <= dot(jury, upper_cake[r+1])) ++r;

    winning_cake[l] += 1;
    winning_cake[r+1] -= 1;
  }

  for (int i = 1; i < winning_cake.size(); ++i) winning_cake[i] += winning_cake[i-1];

  map<pair<int, int>, int> mapCakeToIdx;
  for (int i = 0; i < cakes.size(); ++i) mapCakeToIdx[cakes[i]] = i;

  for (int i = 0; i < upper_cake.size(); ++i) ans[mapCakeToIdx[upper_cake[i]]] = winning_cake[i];

  for (int i = 0; i < n; ++i) printf("%d\n", ans[i]);
  return 0;
}
