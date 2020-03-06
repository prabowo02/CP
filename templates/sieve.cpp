/** Cache-friendly sieve **/

namespace Sieve {

const int N = 1e7;

// Tune this
const int SEG_SIZE = 10000;

bool is_prime[N];
vector<int> primes;
void sieve(int n) {
  is_prime[2] = true;
  for (int i = 3; i <= n; i += 2) is_prime[i] = true;
  primes = {2};

  for (int st = 3; st <= n; st += SEG_SIZE) {
    int en = (st + SEG_SIZE < n+1 ? st + SEG_SIZE : n+1);
    for (int i = 1; i < primes.size(); ++i) {
      int p = primes[i];
      if (p*p >= en) break;
      int s = (st <= p ? p+p : (st/p + (st%p != 0)) * p);
      for (int j = s; j < en; j += p) {
        is_prime[j] = false;
      }
    }

    for (int i = st; i < en; i += 2) {
      if (!is_prime[i]) continue;
      primes.push_back(i);
      if (1LL*i*i < en) for (int j = i*i; j < en; j += i) {
        is_prime[j] = false;
      }
    }
  }
}
}

/** Cache-friendly segmented sieve **/

namespace SegmentedSieve {

const int N = 1e9;
const int S = sqrt(N);

// Tune this
const int SEG_SIZE = 10000;

bool sieve[S];
bool segmented[N];
int primes[S];
void segmented_sieve(int l, int r) {
  for (int i = 0; i*i <= r; ++i) sieve[i] = true;
  for (int i = l; i <= r; ++i) segmented[i-l] = true;

  int pcount = 0;
  for (int p = 2; p*p <= r; ++p) {
    if (!sieve[p]) continue;
    primes[pcount++] = p;
    for (int j = p*2; 1LL*j*j <= r; j += p) sieve[j] = false;
  }

  for (int i = l; i <= r; i += SEG_SIZE) {
    for (int j = 0; j < pcount; ++j) {
      int p = primes[j];
      int st = (i <= p ? p+p : (i/p + (i%p != 0)) * p);
      for (int k = st; k < i + SEG_SIZE; k += p) segmented[k-l] = false;
    }
  }
}

}
