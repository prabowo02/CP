#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, k;
char s[N];
int e[N];

vector<int> edges[N];

void read() {
  scanf("%d %d", &n, &k);
  scanf("%s", s);

  for (int i = 0; i < n; ++i) edges[i].clear();

  int a, b, c;

  for (int i = 1; i < k+1; ++i) {
    scanf("%d", &e[i]);
    edges[e[i] - 1].push_back(i);
  }
  scanf("%d %d %d", &a, &b, &c);
  for (int i = k+1; i < n; ++i) {
    e[i] = (1LL * a * e[i-2] + 1LL * b * e[i-1] + c) % i + 1;
    edges[e[i] - 1].push_back(i);
  }
}

int szCovid[N], root[N];
int dfsCovid(int u, int r) {
  szCovid[u] = 1;
  root[u] = r;
  for (int v: edges[u]) {
    if (s[v] == '#') {
      continue;
    }
    szCovid[u] += dfsCovid(v, r);
  }

  return szCovid[u];
}

int sz[N];
int dfsSz(int u) {
  sz[u] = 1;
  for (int v: edges[u]) {
    sz[u] += dfsSz(v);
  }
  return sz[u];
}

long long dfsAns(int u, int r=-2) {
  long long ret = 0;
  for (int v: edges[u]) {
    ret += dfsAns(v, r);

    if (root[u] == r && root[v] == r) {
      ret += 1LL * szCovid[v] * (szCovid[r] - szCovid[v]);
    } else {
      ret += 1LL * sz[v] * (n - sz[v]);
    }
  }

  return ret;
}

int szLarge[N], szLarge2[N];;
long long dfsSzLarge(int u, int target, int szLarge[]) {
  szLarge[u] = (root[u] != -1 && szCovid[root[u]] == target);
  for (int v: edges[u]) {
    szLarge[u] += dfsSzLarge(v, target, szLarge);
  }
  return szLarge[u];
}

long long dfsAns2(int u, int sz1, int sz2) {
  long long ret = 0;
  for (int v: edges[u]) {
    ret += dfsAns2(v, sz1, sz2);

    if (root[u] != -1 && root[v] != -1) continue;

    if (sz1 == sz2) {
      ret += 1LL * szLarge[v] * (szLarge[0] - szLarge[v]);
    } else {
      ret += 1LL * szLarge[v] * (szLarge2[0] - szLarge2[v]);
      ret += 1LL * szLarge2[v] * (szLarge[0] - szLarge[v]);
    }
  }

  return ret;
}

int solve() {
  read();
  for (int i = 0; i < n; ++i) root[i] = -1;
  dfsSz(0);

  vector<int> v;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '#') continue;
    if (i > 0 && s[e[i] - 1] != '#') continue;
    v.push_back(dfsCovid(i, i));
  }

  sort(v.begin(), v.end(), greater<int>());
  // for (int u: v) cerr << u << endl; cerr << endl;

  if (v.size() == 0) {
    printf("0 %lld\n", dfsAns(0));
    return 0;
  }

  if (v.size() == 1) {
    int idx = -1;
    for (int i = 0; i < n; ++i) {
      if (root[i] != -1) {
        idx = root[i];
        break;
      }
    }

    printf("%lld %lld\n", 1LL * v[0] * (v[0] - 1) / 2, dfsAns(0, idx));
    return 0;
  }

  if (v[0] == v[1]) {
    long long pairs = 1LL * v[0] * (v[0] * 2 - 1);
    for (int i = 2; i < v.size(); ++i) {
      pairs += 1LL * v[i] * (v[i] - 1) / 2;
    }

    dfsSzLarge(0, v[0], szLarge);

    printf("%lld %lld\n", pairs, dfsAns2(0, v[0], v[0]));
    return 0;
  }

  long long pairs = 1LL * (v[0] + v[1]) * (v[0] + v[1] - 1) / 2;
  for (int i = 2; i < v.size(); ++i) {
    pairs += 1LL * v[i] * (v[i] - 1) / 2;
  }

  dfsSzLarge(0, v[0], szLarge);
  dfsSzLarge(0, v[1], szLarge2);

  printf("%lld %lld\n", pairs, dfsAns2(0, v[0], v[1]));
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
