// O(N^2)

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int eval(const vector<int> &p, int x) {
  int ret = 0, mul = 1;
  for (int i = 0; i < p.size(); ++i) {
    ret = (1LL * p[i] * mul + ret) % MOD;
    mul = 1LL * mul * x % MOD;
  }
  return ret;
}

vector<int> interpolate(vector<int> y) {
  vector<int> poly = {1};
  for (int i = 0; i < y.size(); ++i) {
    // multiply (x - i)
    poly.push_back(poly.back());
    int m = (i == 0 ? 0 : MOD - i);
    for (int j = (int) poly.size() - 2; j > 0; --j) {
      poly[j] = (poly[j - 1] + 1LL * poly[j] * m) % MOD;
    }
    poly[0] = 1LL * poly[0] * m % MOD;
  }

  vector<int> res(y.size());
  for (int i = 0; i < y.size(); ++i) {
    vector<int> p = poly;
    // divide (x - i)
    if (i == 0) {
      for (int i = 1; i < p.size(); ++i) p[i - 1] = p[i];
      p.pop_back();
    } else {
      int m = power(MOD - i, MOD - 2);
      p[0] = 1LL * p[0] * m % MOD;
      for (int j = 1; j + 1 < p.size(); ++j) {
        p[j] = 1LL * (p[j] - p[j - 1]) * m % MOD;
        if (p[j] < 0) p[j] += MOD;
      }
      p.pop_back();
    }

    m = 1LL * y[i] * power(eval(p, i), MOD - 2) % MOD;
    for (int j = 0; j < y.size(); ++j) {
      res[j] = (res[j] + 1LL * m * p[j]) % MOD;
    }
  }

  return res;
}
