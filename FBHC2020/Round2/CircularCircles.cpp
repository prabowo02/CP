#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int MOD = 1000000007;

int n, m, e, k;
int X[N], Y[N], I[N], W[N];

int weights[N];
multiset<int> pq[N][2];
multiset<int> pqlarge;

void readArray(int k, int n, int arr[], int mod) {
  for (int i = 0; i < k; ++i) {
    scanf("%d", &arr[i]);
  }

  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  for (int i = k; i < n; ++i) {
    arr[i] = (1LL * arr[i-2] * a + 1LL * arr[i-1] * b + c) % mod;
  }
}

void read() {
  scanf("%d %d %d %d", &n, &m, &e, &k);
  readArray(k, n, X, m);
  readArray(k, n, Y, m);
  readArray(k, e, I, n*m + n);
  readArray(k, e, W, 1000000000);
}

int solve() {
  read();

  for (int i = 0; i < n; ++i) {
    if (Y[i] < X[i]) swap(X[i], Y[i]);
    pq[i][0].clear(); pq[i][1].clear();
    pq[i][0].insert(0); pq[i][1].insert(0);

    for (int j = 0; j < X[i]; ++j) {
      weights[i*m + j] = 1;
      pq[i][0].insert(1);
    }

    for (int j = X[i]; j < Y[i]; ++j) {
      weights[i*m + j] = 1;
      pq[i][1].insert(1);
    }

    for (int j = Y[i]; j < m; ++j) {
      weights[i*m + j] = 1;
      pq[i][0].insert(1);
    }
  }

  pqlarge.clear();
  for (int i = 0; i < n; ++i) {
    weights[n*m + i] = 1;
    pqlarge.insert(1);
    pqlarge.insert(min(*pq[i][0].rbegin(), *pq[i][1].rbegin()));
  }

  long long sum = n*m + m, maxi = m + 1;

  int ans = 1;
  for (int i = 0; i < e; ++i) {
    // cerr << i << " " << I[i] << " " << W[i] << " " << weights[I[i]] << endl;
    sum -= weights[I[i]];

    if (I[i] < n*m) {
      int circle = I[i] / m, idx = I[i] % m;

      int m0 = *pq[circle][0].rbegin(), m1 = *pq[circle][1].rbegin();

      maxi -= *pqlarge.rbegin();
      pqlarge.erase(pqlarge.find(min(m0, m1)));

      maxi -= max(m0, m1);

      if (X[circle] <= idx && idx < Y[circle]) {
        pq[circle][1].erase(pq[circle][1].find(weights[I[i]]));
        pq[circle][1].insert(W[i]);
      } else {
        pq[circle][0].erase(pq[circle][0].find(weights[I[i]]));
        pq[circle][0].insert(W[i]);
      }

      m0 = *pq[circle][0].rbegin(), m1 = *pq[circle][1].rbegin();

      maxi += max(m0, m1);

      pqlarge.insert(min(m0, m1));
      maxi += *pqlarge.rbegin();
    } else {
      maxi -= *pqlarge.rbegin();
      pqlarge.erase(pqlarge.find(weights[I[i]]));
      pqlarge.insert(W[i]);
      maxi += *pqlarge.rbegin();
    }

    sum += weights[I[i]] = W[i];

    ans = 1LL * ans * ((sum - maxi) % MOD) % MOD;
  }

  printf("%d\n", ans);
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
