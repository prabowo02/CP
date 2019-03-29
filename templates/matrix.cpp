#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;;

const int SZ = 100;
struct Matrix {
  int a[SZ][SZ];
  
  Matrix(int val = 0) {
    for (int i=0; i<SZ; i++) {
      for (int j=0; j<SZ; j++) a[i][j] = 0;
      a[i][i] = val;
    }
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret;
    for (int i=0; i<SZ; i++) {
      for (int j=0; j<SZ; j++) {
        for (int k=0; k<SZ; k++) {
          ret.a[i][j] = (1LL * a[i][k] * other.a[k][j] + ret.a[i][j]) % MOD;
        }
      }
    }
    
    return ret;
  }
};

Matrix power(Matrix A, long long y) {
  Matrix ret(1);
  
  for (; y; y >>= 1) {
    if (y & 1) ret = ret * A;
    A = A * A;
  }
  
  return ret;
}

int main() {

  return 0;
}
