// TYPE | MAT | INVMAT
// XOR | [[1, 1], [1, -1]] | [[1, 1], [1, -1]]
// AND | [[0, 1], [1, 1]] | [[-1, 1], [1, 0]]
// OR | [[1, 1], [1, 0]] | [[0, 1], [1, -1]]
void fwht(vector<long long> &data, int dim, bool inverse) {
  int mat[2][2] = {{1, 1}, {1, -1}};
  int invmat[2][2] = {{1, 1}, {1, -1}};
  
  for (int len = 1; 2 * len <= dim; len <<= 1) {
    for (int i = 0; i < dim; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        long long a = data[i + j];
        long long b = data[i + j + len];


        if (!inverse) {
          data[i + j] = (mat[0][0] * a + mat[0][1] * b) % MOD;
          data[i + j + len] = (mat[1][0] * a + mat[1][1] * b) % MOD;
        } else {
          data[i + j] = (invmat[0][0] * a + invmat[0][1] * b) % MOD;
          data[i + j + len] = (invmat[1][0] * a + invmat[1][1] * b) % MOD;
        }
      }
    }
  }
}
