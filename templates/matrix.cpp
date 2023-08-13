#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

/**
const int SZ = 10;
struct Matrix {
  int a[SZ][SZ];
  
  Matrix(int val = 0) {
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        a[i][j] = 0;
      }
      a[i][i] = val;
    }
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret;
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        for (int k = 0; k < SZ; ++k) {
          ret.a[i][j] = (1LL * a[i][k] * other.a[k][j] + ret.a[i][j]) % MOD;
        }
      }
    }
    
    return ret;
  }
  
  void print() {
    for (int i = 0; i < SZ; ++i) {
      for (int j = 0; j < SZ; ++j) {
        printf("%d ", a[i][j]);
      }
      printf("\n");
    }
  }
};
*/

// Matrix with dynamic size during init
struct Matrix {
  int n, **a;
  
  Matrix(int _n, int val = 0) {
    n = _n;
    a = (int **) malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; ++i) {
      a[i] = (int *) malloc(n * sizeof(int));
      for (int j = 0; j < n; ++j) {
        a[i][j] = 0;
      }
      a[i][i] = val;
    }
  }
  
  ~Matrix() {
    for (int i = 0; i < n; ++i) free(a[i]);
    free(a);
  }
  
  Matrix operator * (const Matrix &other) {
    Matrix ret(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          ret.a[i][j] = (1LL * a[i][k] * other[k][j] + ret[i][j]) % MOD;
        }
      }
    }
    
    return ret;
  }
  
  int * operator [] (int row) const {
    return a[row];
  }
  
  void print() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        printf("%d ", a[i][j]);
      }
      printf("\n");
    }
  }
};

Matrix power(Matrix A, long long y) {
  Matrix ret(A.n, 1);
  
  for (; y; y >>= 1) {
    if (y & 1) ret = ret * A;
    A = A * A;
  }
  
  return ret;
}

int main() {
  Matrix A(2);
  A[0][0] = A[1][0] = A[0][1] = 1;
  power(A, 4).print();
  return 0;
}
