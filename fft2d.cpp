#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

namespace FFT {

const int MAXN = 1 << 16;

complex<double> w[MAXN];

void init() {
  for (int i = 0; i < MAXN; ++i) {
    w[i] = complex<double>(cos(2*PI*i / MAXN), sin(2*PI*i / MAXN));
  }
}

void _fft(int n, vector<complex<double>> &a) {
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    int wlen = MAXN / len;
    for (int i = 0; i < n; i += len) {
      for (int j = 0; j < len>>1; j++) {
        complex<double> u = a[i+j];
        complex<double> v = a[i+j + len/2] * w[wlen * j];

        a[i+j] = u + v;
        a[i+j + len/2] = u - v;
      }
    }
  }
}

void fft(int n, vector<complex<double>> &a, bool inverse) {
  if (inverse) {
    reverse(a.begin() + 1, a.end());
  }
  _fft(n, a);
  if (inverse) {
    for (int i = 0; i < n; ++i) a[i] /= n;
  }
}

void fft2d(int n, int m, vector<vector<complex<double>>> &a, bool inverse) {
  for (int i = 0; i < n; ++i) {
    fft(m, a[i], inverse);
  }
  for (int j = 0; j < m; ++j) {
    vector<complex<double>> b(n);
    for (int i = 0; i < n; ++i) b[i] = a[i][j];
    fft(n, b, inverse);
    for (int i = 0; i < n; ++i) a[i][j] = b[i];
  }
}

}

vector<vector<complex<double>>> conv2d(vector<vector<complex<double>>> a, vector<vector<complex<double>>> b) {
  int n = 1, degN = a.size() + b.size() - 1;
  while (n < degN) n <<= 1;
  int m = 1, degM = a[0].size() + b[0].size() - 1;
  while (m < degM) m <<= 1;

  a.resize(n); b.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i].resize(m);
    b[i].resize(m);
  }

  FFT::fft2d(n, m, a, false); FFT::fft2d(n, m, b, false);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] *= b[i][j];
    }
  }
  FFT::fft2d(n, m, a, true);

  a.resize(degN);
  for (int i = 0; i < n; ++i) {
    a[i].resize(degM);
  }
  return a;
}

int main() {
  FFT::init();
  return 0;
}
