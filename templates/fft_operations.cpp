// All is N log N, unless otherwise specified

const int MOD = 998244353;

// O(N)
vector<int> add(vector<int> a, vector<int> b) {
  if (a.size() < b.size()) swap(a, b);
  for (int i = 0; i < b.size(); ++i) a[i] = (a[i] + b[i]) % MOD;
  return a;
}

// O(N)
vector<int> subtract(vector<int> a, vector<int> b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < b.size(); ++i) a[i] = (a[i] - b[i] + MOD) % MOD;
  return a;
}

// O(N^2)
vector<int> multiply_small(vector<int> a, vector<int> b) {
  vector<int> c(a.size() + b.size() - 1);
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      c[i+j] = (1LL * a[i] * b[j] + c[i+j]) % MOD;
    }
  }
  return c;
}

vector<int> multiply_large(vector<int> a, vector<int> b) {
  int len = (a.size() + b.size() == 2 ? 1 : 1 << (32 - __builtin_clz(a.size() + b.size() - 2)));
  a.resize(len); b.resize(len);
  fft(len, a, false); fft(len, b, false);
  a.resize(len);
  for (int i = 0; i < len; ++i) a[i] = 1LL * a[i] * b[i] % MOD; 
  fft(len, a, true);
  return a;
}

vector<int> multiply(vector<int> a, vector<int> b) {
  if (1LL * a.size() * b.size() <= 5000) return multiply_small(a, b);
  return multiply_large(a, b);
}

// O(N)
vector<int> differentiate(vector<int> a) {
  for (int i = 0; i+1 < a.size(); ++i) a[i] = 1LL * a[i+1] * (i+1) % MOD;
  a.pop_back();
  return a;
}

// O(N)
vector<int> integral(vector<int> a) {
  a.resize(a.size() + 1);
  for (int i = (int) a.size() - 1; i > 0; --i) a[i] = 1LL * a[i-1] * power(i, MOD-2) % MOD;
  a[0] = 0;
  return a;
}

vector<int> quotient(vector<int> a, vector<int> b) {
  int qlen = 1 << 32 - __builtin_clz(n - m);
  reverse(a.begin(), a.end()); reverse(b.begin(), v.end());
  a.resize(qlen); b.resize(qlen);
  vector<int> result = multiply(a, b);
  result.resize(n-m+1);
  reverse(result.begin(), result.end());
  return result;
}

vector<int> modulo(vector<int> a, vector<int> b) {
  if (a.size() < b.size()) return a;
  return subtract(a, multiply(b, quotient(a, b)));
}

// PQ = 1
// (PQ - 1)^2 = 0
// 1 = P(2Q - PQ^2)
// Q' = 2Q - PQ^2
vector<int> inverse(int n, vector<int> a) {
  a.resize(n*2);
  vector<int> res = {power(a[0], MOD-2)};
  for (int len = 2; len < n<<1; len <<= 1) {
    vector<int> tmp = multiply(multiply(res, res), vector<int>(a.begin(), a.begin() + len));
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = (2LL * res[i] - tmp[i] + MOD) % MOD;
  }
  res.resize(n);
  return res;
}

// Q^2 - P = 0
// Q' = Q - (Q^2 - P) / 2Q = 1/2 Q + 1/2 P/Q
vector<int> squareRoot(int n, vector<int> a) {
  // supposed to be sqrt(a[0]), find its sqrt if necessary
  vector<int> res = {1};
  a.resize(n*2);
  const int INV2 = power(2, MOD-2);
  for (int len = 2; len < n<<1; len <<= 1) {
    vector<int> tmp = multiply(vector<int>(a.begin(), a.begin() + len), inverse(n, res));
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = 1LL * INV2 * (res[i] + tmp[i]) % MOD;
  }
  res.resize(n);
  return res;
}

// integral P'/P
vector<int> log(int n, vector<int> a) {
  vector<int> ret = multiply(differentiate(a), inverse(n, a));
  ret.resize(n-1);
  return integral(ret);
}

// log(Q) - P = 0
// Q' = Q - (log(Q) - P) Q
vector<int> exp(int n, vector<int> a) {
  // Assume a[0] = 0
  vector<int> res = {1};
  a.resize(n*2);
  for (int len = 2; len < n<<1; len <<= 1) {
    vector<int> sub(len); for (int i = 0; i < len; ++i) sub[i] = (res[i] - a[i] + MOD) % MOD;
    vector<int> tmp = multiply(sub, res);
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = (res[i] - tmp[i] + MOD) % MOD;
  }
  res.resize(n);
  return res;
}

vector<int> power(int n, vector<int> a, int k) {
  vector<int> ret = log(n, a);
  for (int i = 0; i < n; ++i) ret[i] = 1LL * ret[i] * k % MOD;
  return exp(n, ret);
}

// Computes prod(x - points_i) in N log^2
void _products(int node, int l, int r, const vector<int> &points, vector<int> results[]) {
  if (l == r) {
    result[node] = {points[l] == 0 ? 0 : MOD - points[l], 1};
    return;
  }
  int mid = (l + r) >> 1;
  _product(node*2 + 1, result, l, mid+0, points);
  _product(node*2 + 2, result, mid+1, r, points);
  result[node] = multiply(result[node*2 + 1], result[node*2 + 2]);
}

// N log^2
void _multipointEvaluations(int node, int l, int r, vector<int> poly, vector<int> prods[], vector<int> &results) {
  if (l == r) {
    results[l] = poly[0];
    return;
  }
  _multipointEvaluations(node*2 + 1, l, mid+0, modulo(poly, prods[node*2 + 1]), prods, results);
  _multipointEvaluations(node*2 + 2, mid+1, r, modulo(poly, prods[node*2 + 2]), prods, results);
}

// N log^2
vector<int> multipointEvaluations(vector<int> points, vector<int> polynom) {
  vector<int> products(points.size() * 4), result(points.size());
  _products(0, 0, (int) points.size() - 1, points, products);
  _multipointEvaluations(0, 0, n-1, polynom, products, result);
  return result;
}
