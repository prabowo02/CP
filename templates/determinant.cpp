int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int mat[K][K];
int det(int n, int a[K][K]) {
  int ret = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[j][i] == 0) continue;
      ret = (MOD - ret);
      for (int k = i; k < n; ++k) {
        swap(a[i][k], a[j][k]);
      }
      break;
    }
    if (a[i][i] == 0) return 0;
    ret = 1LL * ret * a[i][i] % MOD;

    int inv = power(a[i][i], MOD - 2);
    for (int j = i + 1; j < n; ++j) {
      int mul = -1LL * a[j][i] * inv % MOD;
      if (mul < 0) mul += MOD;
      for (int k = i; k < n; ++k) {
        a[j][k] = (a[j][k] + 1LL * mul * a[i][k]) % MOD;
      }
    }
  }

  return ret;
}
