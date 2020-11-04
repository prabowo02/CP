namespace DFT {
 
const int MAXVAL = 5000;
 
int mod = -1, in;
vector<int> zp, izp;
 
// Call this again for another mod
void initDft(int n) {
  if (mod == -1) mod = MAXVAL / n * n + n + 1;
  else mod += n;
 
  while (!isPrime(mod)) mod += n;
  in = power(n, mod - 2, mod);
 
  int z = power(primitiveRoot(mod), (mod-1) / n, mod);
  int iz = power(z, mod - 2, mod);
 
  int len = n*2 - 1;
  zp.assign(len, z), izp.assign(len, iz);
  zp[0] = zp[1] = izp[0] = izp[1] = 1;
 
  for (int k = 0; k < 2; ++k) {
    for (int i = 2; i < len; ++i) {
      zp[i] = 1LL * zp[i] * zp[i-1] % mod;
      izp[i] = 1LL * izp[i] * izp[i-1] % mod;
    }
  }
}
 
void dft(vector<int> &a, bool invert) { // Chirp-Z Transform
  if (invert) swap(zp, izp);
 
  vector<int> A(a.size());
  for (int i = 0; i < a.size(); ++i) {
    A[a.size() - i - 1] = 1LL * a[i] * izp[i] % mod;
  }
  A = FFT::multiply(A, zp, mod);
 
  for (int i = 0; i < a.size(); ++i) {
    a[i] = 1LL * A[i + a.size() - 1] * izp[i] % mod;
  }
 
  if (invert) {
    swap(zp, izp);
    for (int i = 0; i < a.size(); ++i) a[i] = 1LL * a[i] * in % mod;
  } 
}
 
}