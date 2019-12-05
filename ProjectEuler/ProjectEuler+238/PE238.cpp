#include <bits/stdc++.h>
using namespace std;

const int MOD = 1004535809;

int a[20973];
int pos[89060];

string get_string_tour() {
  stringstream ss;
  ss << 4;

  const int MOD = 16710461;
  auto p5 = [](int n) {
    long long tmp = 1LL * n * n % MOD;
    return 1LL * tmp * tmp % MOD * n % MOD;
  };

  for (int cur = 4, nxt; (nxt = p5(cur)) != 4; cur = nxt) {
    cur = nxt;
    ss << cur;
  }

  return ss.str();
}

void compute_pos() {
  string s = get_string_tour();
  int n = s.size();

  for (int i = 0; i < n; ++i) a[i] = s[i] - '0';

  pos[0] = 1;
  for (int i = 0; i < 50; ++i) {
    int sum = 0;
    for (int j = i; j < n; ++j) {
      sum += a[j];
      if (pos[sum] == 0) pos[sum] = i + 1;
    }

    for (int j = 0; j < i-1; ++j) {
      sum += a[j];
      if (pos[sum] == 0) pos[sum] = i + 1;
    }
  }
}

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

namespace FFT {

/* ----- Adjust the constants here ----- */
const int LN = 21;
const int N = 1 << LN;

// `MOD` must be of the form 2**`LN` * k + 1, where k odd.
const int MOD = 1004535809; // 2**21 * 479 + 1.
const int PRIMITIVE_ROOT = 3; // Primitive root modulo `MOD`.
/* ----- End of constants ----- */

int root[N];

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, MOD-1 >> LN);
  root[0] = 1;
  for (int i=1; i<N; i++) {
    root[i] = 1LL * UNITY * root[i-1] % MOD;
  }
}

// n = 2^k is the length of polynom
void fft(int n, int a[], bool invert) {
  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len=2; len<=n; len<<=1) {
    int wlen = (invert ? root[N - N/len] : root[N/len]);
    for (int i=0; i<n; i+=len) {
      int w = 1;
      for (int j=0; j<len>>1; j++) {
        int u = a[i+j];
        int v = 1LL * a[i+j + len/2] * w % MOD;

        a[i+j] = (u + v) % MOD;
        a[i+j + len/2] = (u - v + MOD) % MOD;

        w = 1LL * w * wlen % MOD;
      }
    }
  }

  if (invert) {
    int inv = power(n, MOD-2);
    for (int i=0; i<n; i++) a[i] = 1LL * a[i] * inv % MOD;
  }
}

// n = 2^k is the length of inverse polynom
int ret[N];
int a_mod[N];
int tmp_ret[N];
void inverse(int n, int a[]) {
  ret[0] = power(a[0], MOD-2);
  a_mod[0] = a[0];

  for (int len = 2; len <= n; len *= 2) {
    for (int i = len; i < len*2; ++i) ret[i] = a_mod[i] = 0;
    for (int i = 0; i < len; ++i) {
      a_mod[i] = a[i];
    }

    for (int i = 0; i < len; ++i) tmp_ret[i] = ret[i];

    fft(len*2, ret, false);
    for (int i = 0; i < len*2; ++i) ret[i] = 1LL * ret[i] * ret[i] % MOD;
    fft(len*2, ret, true);

    for (int i = len; i < len*2; ++i) ret[i] = 0;

    fft(len*2, ret, false); fft(len*2, a_mod, false);
    for (int i = 0; i < len*2; ++i) ret[i] = 1LL * ret[i] * a_mod[i] % MOD;
    fft(len*2, ret, true);

    for (int i = 0; i < len; ++i) {
      ret[i] = (2LL * tmp_ret[i] - ret[i] + MOD) % MOD;
    }
  }

  for (int i = 0; i < n; ++i) a[i] = ret[i];
}

// n is degree of a, m is degree of b
int tmpa[N], tmpb[N];
void quotient(int n, int a[], int m, int b[], int result[]) {
  int qlen = 1 << 32 - __builtin_clz(n - m);

  for (int i = 0; i <= n; ++i) tmpa[i] = a[i];
  for (int i = 0; i <= m; ++i) tmpb[i] = b[i];

  reverse(a, a + n+1);
  reverse(b, b + m+1);

  for (int i = n+1; i < qlen; ++i) a[i] = 0;
  for (int i = m+1; i < qlen; ++i) b[i] = 0;

  inverse(qlen, b);

  for (int i = qlen; i < qlen*2; ++i) a[i] = b[i] = 0;

  fft(qlen*2, a, false); fft(qlen*2, b, false);

  for (int i = 0; i < qlen*2; ++i) result[i] = 1LL * a[i] * b[i] % MOD;

  fft(qlen*2, result, true);

  for (int i = 0; i <= n; ++i) a[i] = tmpa[i];
  for (int i = 0; i <= m; ++i) b[i] = tmpb[i];

  reverse(result, result + n-m + 1);
}

// vector<int> a = {MOD-12, MOD-4, 3, 1};
// vector<int> b = {MOD-6, 1, 1};
// vector<int> q = FFT::quotient(3, a, 2, b);
// vector<int> r = FFT::modulo(3, a, 2, b);

// for (int u: q) cerr << u << " "; cerr << endl;
// for (int u: r) cerr << u << " "; cerr << endl;

int q[N];
void modulo(int n, int a[], int m, int b[], int result[]) {
  if (n < m) {
    for (int i = 0; i <= n; ++i) result[i] = a[i];
    return;
  }

  quotient(n, a, m, b, q);

  int len = 1 << 32 - __builtin_clz(m);

  for (int i = n-m+1; i < len*2; ++i) q[i] = 0;
  for (int i = m+1; i < len*2; ++i) b[i] = 0;

  fft(len*2, b, false); fft(len*2, q, false);
  for (int i = 0; i < len*2; ++i) {
    result[i] = (1LL * b[i] * q[i]) % MOD;
  }
  fft(len*2, result, true);

  for (int i = 0; i < m; ++i) result[i] = (a[i] - result[i] + MOD) % MOD;
}

// Computes prod(x - points_i)
int res1[N], res2[N];
void product(int node, vector<int> result[], int l, int r, int points[]) {
  if (l == r) {
    result[node] = {points[l] == 0 ? 0 : MOD - points[l], 1};
    return;
  }

  int mid = l + r >> 1;
  product(node*2 + 1, result, l, mid+0, points);
  product(node*2 + 2, result, mid+1, r, points);

  int len1 = result[node*2 + 1].size();
  int len2 = result[node*2 + 2].size();
  int len = 1 << 32 - __builtin_clz(len1 + len2 - 2);

  for (int i = 0; i < len1; ++i) res1[i] = result[node*2 + 1][i];
  for (int i = 0; i < len2; ++i) res2[i] = result[node*2 + 2][i];

  for (int i = len1; i < len; ++i) res1[i] = 0;
  for (int i = len2; i < len; ++i) res2[i] = 0;

  fft(len, res1, false); fft(len, res2, false);
  for (int i = 0; i < len; ++i) res1[i] = 1LL * res1[i] * res2[i] % MOD;
  fft(len, res1, true);

  result[node] = vector<int>(res1, res1 + len1 + len2 - 1);
}

int poly[N];
int subp[N];
int modu[N];
void multipoint_evaluations(int node, int results[], int l, int r, const vector<int> &polynom, vector<int> subprods[]) {
  if (l == r) {
    results[l] = polynom[0];
    return;
  }

  int mid = l + r >> 1;

  for (int i = 0; i < polynom.size(); ++i) poly[i] = polynom[i];
  for (int i = 0; i < subprods[node*2 + 1].size(); ++i) subp[i] = subprods[node*2 + 1][i];
  modulo(polynom.size() - 1, poly, subprods[node*2 + 1].size() - 1, subp, modu);

  multipoint_evaluations(node*2 + 1, results, l, mid+0,
    vector<int>(modu, modu + subprods[node*2 + 1].size() - 1), subprods
  );

  for (int i = 0; i < polynom.size(); ++i) poly[i] = polynom[i];
  for (int i = 0; i < subprods[node*2 + 2].size(); ++i) subp[i] = subprods[node*2 + 2][i];
  modulo(polynom.size() - 1, poly, subprods[node*2 + 2].size() - 1, subp, modu);

  multipoint_evaluations(node*2 + 2, results, mid+1, r,
    vector<int>(modu, modu + subprods[node*2 + 2].size() - 1), subprods
  );
}

// vector<int> p = {1, 3, 2};
// int points[5] = {0, 1, 2, 3, 4};
// FFT::multipoint_evaluations(5, points, p);
// for (int i = 0; i < 5; ++i) cerr << points[i] << endl;
void multipoint_evaluations(int n, int points[], const vector<int> &p) {
  vector<int> subprods[n*4];

  product(0, subprods, 0, n-1, points);

  multipoint_evaluations(0, points, 0, n-1, p, subprods);
}

}

// Computes {n+1, 1 + 2 + ... + n, 1^2 + 2^2 + ... + n^2, ..., 1^k + 2^k + ... + n^k}
int e[FFT::N];
int e2[FFT::N];
int e3[FFT::N];
vector<int> sum_of_power(long long n, int k) {
  n %= MOD;
  int len = 1 << 32 - __builtin_clz(k);

  for (int i = len; i < len*2; ++i) e[i] = e2[i] = e3[i] = 0;

  // e^x
  e[0] = 1;
  for (int i = 1; i < len; ++i) {
    e[i] = 1LL * e[i-1] * power(i, MOD-2) % MOD;
  }

  // (e^nx - 1) / x
  for (int i = 1; i < len; ++i) {
    e2[i-1] = 1LL * e[i] * power(n, i) % MOD;
  }
  e2[len-1] = 1LL * e[len-1] * power(len, MOD-2) % MOD * power(n, len) % MOD;


  FFT::fft(len*2, e, false); FFT::fft(len*2, e2, false);

  for (int i = 0; i < len*2; ++i) {
    e[i] = 1LL * e[i] * e2[i] % MOD;
  }

  FFT::fft(len*2, e, true);

  for (int i = len; i < len*2; ++i) e[i] = 0;

  // (e^x - 1) / x
  e3[0] = 1;
  for (int i = 1; i < len; ++i) {
    e3[i] = 1LL * e3[i-1] * power(i+1, MOD-2) % MOD;
  }
  FFT::inverse(len, e3);

  FFT::fft(len*2, e, false); FFT::fft(len*2, e3, false);
  for (int i = 0; i < len*2; ++i) {
    e[i] = 1LL * e[i] * e3[i] % MOD;
  }
  FFT::fft(len*2, e, true);

  cerr << k << endl;

  vector<int> ret; int fact = 1;
  for (int i = 0; i <= k; ++i) {
    ret.push_back(1LL * e[i] * fact % MOD);
    fact = 1LL * fact * (i+1) % MOD;
  }
  ret[0] += 1;

  return ret;
}

void init() {
  compute_pos();
  FFT::init_fft();
}

int brute(int e, long long n) {
  long long ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret = (1LL * pos[i % 89060] * power(i, e) + ret) % MOD;
  }

  return ret;
}

int solve(int e, long long n) {
  if (n < 89060 * 2) {
    return brute(e, n);
  }

  vector<int> polynom = sum_of_power(n / 89060 - 1, e);
  reverse(polynom.begin(), polynom.end());

  int C = 1;
  for (int i = 1; i < e; ++i) {
    C = 1LL * C * (e-i+1) % MOD * power(i, MOD-2) % MOD;
    polynom[i] = 1LL * polynom[i] * C % MOD;
  }

  int e_89060 = 1;
  for (int i = e-1; i >= 0; --i) {
    e_89060 = 1LL * e_89060 * 89060 % MOD;
    polynom[i] = 1LL * polynom[i] * e_89060 % MOD;
  }

  int points[89060];
  iota(points, points + 89060, 0);

  cerr << "Starting multipoint" << endl;
  FFT::multipoint_evaluations(89060, points, polynom);
  cerr << "End multipoint" << endl;

  int ans = (e == 0 ? MOD-1 : 0);
  int nn = ((n / 89060) * 89060) % MOD;
  for (int i = 0; i < 89060; ++i) {
    ans = (1LL * pos[i] * points[i] + ans) % MOD;
    if (i <= n % 89060) {
      ans = (1LL * pos[i] * power(nn + i, e) + ans) % MOD;
    }
  }

  return ans;
}

int main() {
  init();
  
  long long n; int e;
  scanf("%d %lld", &e, &n);
  clock_t t = clock();
  int a[20] = {MOD-12, MOD-4, 3, 1};
  int b[20] = {MOD-6, 1, 1};
  // FFT::inverse(4, b);
  // for (int u: b) cerr << u << " "; cerr << endl;
  printf("%d\n", solve(e, n));

  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
