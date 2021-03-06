// TYPE | MAT | INVMAT
// XOR | [[1, 1], [1, -1]] | [[1, 1], [1, -1]]
// AND | [[1, 1], [0, 1]] | [[1, -1], [0, 1]] // sum over superset
// OR | [[1, 0], [1, 1]] | [[1, 0], [1, -1]] // sum over subset
// NOT: bit inverse the resulting array

void fwht(int n, int a[]) {
  for (int len = 1; len < n; len <<= 1) {
    for (int i = 0; i < n; i += len << 1) {
      for (int j = 0; j < len; ++j) {
        int u = a[i + j], v = a[i + j + len];
        a[i + j] = (u + v) % MOD;
        a[i + j + len] = (u - v) % MOD;
      }
    }
  }
}
