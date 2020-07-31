#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int power(int x, int y, int mod=MOD) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % mod;
    x = 1LL * x * x % mod;
  }
  return ret;
}

namespace Lagrange {

// Given data points (0, y[0]), (1, y[1]), ...
//   which can be represented as a polynomial P
// Compute P(N)

// If data points are x = {1, 2, ...}, change (N - i) to (N - i - 1)
int Lagrange(int N, vector<int> ys) {
  vector<int> sufnum(ys.size(), 1);
  for (int i = (int) ys.size() - 1; i > 0; --i) {
    sufnum[i-1] = 1LL * sufnum[i] * (N - i) % MOD;
  }

  int fact = 1;
  for (int i = 1; i < ys.size(); ++i) fact = 1LL * fact * i % MOD;
  fact = power(fact, MOD-2);

  vector<int> ifact(ys.size());
  for (int i = (int) ys.size() - 1; i >= 0; --i) {
    ifact[i] = fact;
    fact = 1LL * fact * i % MOD;
  }

  int ret = 0, prenum = 1;
  for (int i = 0; i < ys.size(); ++i) {
    int num = 1LL * prenum * sufnum[i] % MOD;
    int den = 1LL * ifact[i] * ifact[(int) ys.size() - i - 1] % MOD;
    if ((int) ys.size() - i - 1 & 1) den *= -1;

    ret = (ret + 1LL * num * den % MOD * ys[i]) % MOD;

    prenum = 1LL * prenum * (N - i) % MOD;
  }

  if (ret < 0) ret += MOD;
  return ret % MOD;
}

} // namespace Lagrange

int main() {
  int k = 3;
  vector<int> ys = {0};
  for (int i = 1; i <= k+1; ++i) {
    ys.push_back((ys.back() + power(i, k)) % MOD);
  }

  for (int i = 0; i <= 10; ++i) cout << Lagrange::Lagrange(i, ys) << endl;
  return 0;
}
