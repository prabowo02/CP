/* A common library for prime-related problems */

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using std::pair;
using std::sort;
using std::vector;

long long multiply(long long a, long long b, long long m) {
  long long y = (long long) ((long double) a * (long double) b / m + 0.5);
  y = y * m;
  long long x = a * b;
  long long ret = x - y;
  if (ret < 0) ret += m;
  return ret;
}

// x and y are non-negative
long long gcd(long long x, long long y) {
  return y ? gcd(y, x % y) : x;
}

int power_int(int x, int y, int mod) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % mod;
    x = 1LL * x * x % mod;
  }

  return ret;
}

// Used in `isPrime`, `pollardRho`, `primeFactorization`, `countDivisors`. Otherwise, can be replaced with `power_int` for speed
long long power(long long x, long long y, long long mod) {
  long long result = 1;
  long long multiplicator = x % mod;
  for (; y; y >>= 1) {
    if (y & 1) result = multiply(result, multiplicator, mod);
    multiplicator = multiply(multiplicator, multiplicator, mod);
  }
  
  return result;
}

// Assume n >= 2
bool isPrime(long long n) {
  if (n <= 3 || n == 5) return true;
  if (!(n & 1)) return false;

  long long s = __builtin_ctzll(n-1), d = n-1 >> s;
  
  // Adjust the value of `16` accordingly
  for (long long i = 0; i < 16; i++) {
    long long a = rand();
    a <<= 32;
    a += rand();
    a = a % (n - 1) + 2;
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (long long j = 1; j < s; j++) {
      x = multiply(x, x, n);
      if (x == 1) return false;
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

// vector<long long> A_Miller_Rabin = {2, 3, 5, 7}; // N <= 3 * 10^9
// vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11}; // N <= 2 * 10^12
// vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11, 13, 17}; // N <= 3 * 10^14
// vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // N <= 3 * 10^18
vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // N < 2^64
bool isPrime_deterministic(long long n) {
  // Remember to check for all possible of n in A_Miller_Rabin
  if (n <= 3 || n == 5) return true;
  if (!(n & 1)) return false;

  long long s = __builtin_ctzll(n-1), d = n-1 >> s;

  for (long long a: A_Miller_Rabin) {
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (long long j = 1; j < s; j++) {
      x = multiply(x, x, n);
      if (x == 1) return false;
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

// Assume n is not prime
long long pollardRho(long long n) {
  if (n == 1) return n;
  if (n & 1) {
    long long x = (rand() % (n-2)) + 2;
    long long y = x;
    long long c = (rand() % (n-1)) + 1;
    long long d = 1;
    while (d == 1) {
      x = (multiply(x, x, n) + c + n) % n;
      y = (multiply(y, y, n) + c + n) % n;
      y = (multiply(y, y, n) + c + n) % n;
      
      d = gcd(abs(x - y), n);
      if (d == n) return pollardRho(n);
    }
    return d;
  } else return 2;
}

// Returns list of p_k, e_k, where prod(p_k^e_k) = n. p_k is NOT sorted
vector<pair<long long, int>> primeFactorization(long long n) {
  vector<pair<long long, int>> ret;
  
  for (long long p = 2; p*p*p <= n; ++p) {
    if (n % p > 0) continue;
    
    int e = 0;
    do {
      ++e;
      n /= p;
    } while (n % p == 0);
    
    ret.push_back({p, e});
    
    if (n == 1) return ret;
  }

  long long sqrtn = (long long) round(sqrt(n));
  if (sqrtn * sqrtn == n) {
    ret.push_back({sqrtn, 2});
    return ret;
  }
  
  if (isPrime(n)) {
    ret.push_back({n, 1});
    return ret;
  }
  
  long long p = pollardRho(n);
  long long q = n/p;
  
  ret.push_back({p, 1});
  ret.push_back({q, 1});
  return ret;
}

// Return divisors of n = prod(p_k^e_k). Returned list is NOT sorted
vector<long long> divisors(vector<pair<long long, int>> v) {
  vector<long long> ret;
  ret.push_back(1LL);
  
  for (pair<long long, int> pe: v) {
    long long p = pe.first;
    int e = pe.second;
    int sz = ret.size();
    
    for (int i=0; i<sz; i++) {
      long long num = 1;
      for (int j=0; j<e; j++) {
        num *= p;
        ret.push_back(ret[i] * num);
      }
    }
  }
  
  return ret;
}

// Return divisors of n. Returned list is NOT sorted
vector<long long> divisors(long long n) {
  return divisors(primeFactorization(n));
}

int countDivisors(long long n) {
  int ret = 1;
  for (long long p=2; p*p*p <= n; ++p) {
    if (n % p > 0) continue;
    
    int e = 0;
    do {
      ++e;
      n /= p;
    } while (n % p == 0);
    
    ret *= e + 1;
    if (n == 1) return ret;
  }

  long long sqrtn = (long long) round(sqrt(n));
  if (sqrtn * sqrtn == n) return ret * 3;
  
  if (isPrime(n)) return ret * 4;
  
  return ret * 2;
}

void sieve(int n, bool is_prime[]) {
  is_prime[0] = is_prime[1] = false;
  for (int i=2; i<n; i++) is_prime[i] = true;
  
  for (int i=2; i*i<n; i++) {
    if (!is_prime[i]) continue;
    
    for (int j=i*i; j<n; j+=i) {
      is_prime[j] = false;
    }
  }
}

long long euler_phi(long long n) {
  for (pair<long long, int> pe: primeFactorization(n)) {
    long long p = pe.first;
    
    n /= p; n *= p-1;
  }
  
  return n;
}

// p odd prime
int legendre(int n, int p) {
  int ret = power(n, p-1 >> 1, p);
  if (ret == p-1) return -1;
  return ret;
}

// Find a quadratic non-residue of odd prime p
int quadratic_non_residue(int p) {
  int ret = 2;
  while (power(ret, p-1 >> 1, p) == 1) ++ret;
  return ret;
}

int tonelli_shanks(int n, int p) {
  int s = __builtin_ctz(p-1);
  if (s == 1) return power(n, p+1 >> 2, p);
  
  int q = p-1 >> s;
  int z = quadratic_non_residue(p);
  
  int m = s;
  int c = power(z, q, p);
  int t = power(n, q, p);
  int r = power(n, q+1>>1, p);
  
  while (t != 1) {
    int i, tt;
    for (i=1, tt=1LL*t*t%p; tt != 1; ++i, tt=1LL*tt*tt%p);
    
    int b = power(c, 1<<m-i-1, p);
    
    m = i;
    c = 1LL * b * b % p;
    t = 1LL * t * c % p;
    r = 1LL * r * b % p;
  }
  
  return r;
}

// Multiplicative order of n modulo m
long long order(long long n, long long m) {
  vector<int> phi_divisors;
  for (pair<long long, int> pe: primeFactorization(euler_phi(m))) {
    phi_divisors.push_back(pe.first);
  }
  sort(phi_divisors.begin(), phi_divisors.end());
  
  for (int d: phi_divisors) {
    if (power(n, d, m) == 1) return d;
  }
  
  return -1;
}

// Find a primitive root mod p
int primitive_root(int p) {
  vector<int> phi_divisors;
  for (pair<long long, int> pe: primeFactorization(p-1)) {
    phi_divisors.push_back(pe.first);
  }
  sort(phi_divisors.begin(), phi_divisors.end());
  phi_divisors.pop_back();
  
  for (int ret = 2; ; ++ret) {
    bool okay = true;
    
    for (int d: phi_divisors) {
      if (power(ret, d, p) == 1) {
        okay = false;
        break;
      }
    }
    
    if (okay) return ret;
  }
}

int main() {
  
  return 0;
}