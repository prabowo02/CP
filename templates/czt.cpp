vector<int> czt(vector<int> a, int z, int n) {
  int sz = n + a.size() - 1;
  int iz = power(z, MOD-2);

  // zp[i] = z^C(i, 2)
  vector<int> zp(sz), izp(sz);
  zp[0] = zp[1] = izp[0] = izp[1] = 1;

  for (int i = 2; i < sz; ++i) {
    zp[i] = 1LL * zp[i-1] * z % MOD;
    izp[i] = 1LL * izp[i-1] * iz % MOD;
  }

  for (int i = 2; i < sz; ++i) {
    zp[i] = 1LL * zp[i] * zp[i-1] % MOD;
    izp[i] = 1LL * izp[i] * izp[i-1] % MOD;
  }

  vector<int> A(a.size());
  for (int i = 0; i < a.size(); ++i) {
    A[a.size() - i - 1] = 1LL * a[i] * izp[i] % MOD;
  }
  A = multiply(A, zp);

  for (int i = 0; i < n; ++i) {
    A[i] = 1LL * A[i + a.size() - 1] * izp[i] % MOD;
  }
  A.resize(n);
  return A;
}
