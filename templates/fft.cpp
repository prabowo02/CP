#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxn = 100005;

typedef complex<double> ftype;
const double pi = acos(-1);
ftype w[maxn];

template<typename T>
void fft(T *in, T *out, int n, int k)
{
    if(n == 1)
    {
        *out = *in;
        return;
    }
    int t = maxn / n;
    n /= 2;
    fft(in, out, n, 2 * k);
    fft(in + k, out + n, n, 2 * k);
    for(int i = 0, j = 0; i < n; i++, j += t)
    {
        ftype t = w[j] * out[i + n];
        out[i + n] = out[i] - t;
        out[i] = out[i] + t;
    }
}

const int sz = 16, msk = (1 << 16) - 1;

vector<int> mul(vector<int> a, vector<int> b)
{
    int n = a.size() + b.size();
    while(__builtin_popcount(n) != 1)
        n++;
    while(a.size() < n)
        a.push_back(0);
    while(b.size() < n)
        b.push_back(0);
    vector<ftype> A(n), B(n);
    for(int i = 0; i < n; i++)
    {
        A[i] = {a[i] & msk, a[i] >> sz};
        B[i] = {b[i] & msk, b[i] >> sz};
    }
    vector<ftype> nA(n), nB(n);
    ftype w = polar(1., 2 * pi / n);
    fft(A.data(), nA.data(), n, 1);
    fft(B.data(), nB.data(), n, 1);
    
    ftype im2 = {0, 2}, im = {0, 1};
    
    for(int i = 0; i < n; i++)
    {
        ftype lA = (nA[i] + conj(nA[(n - i) % n])) / 2.;
        ftype gA = (nA[i] - conj(nA[(n - i) % n])) / im2;
        ftype lB = (nB[i] + conj(nB[(n - i) % n])) / 2.;
        ftype gB = (nB[i] - conj(nB[(n - i) % n])) / im2;
        A[i] = lA * lB + im * gA * gB;
        B[i] = lA * gB + gA * lB;
    }
    fft(A.data(), nA.data(), n, 1);
    fft(B.data(), nB.data(), n, 1);
    reverse(begin(nA) + 1, end(nA));
    reverse(begin(nB) + 1, end(nB));
    vector<int> ans(n);
    for(int i = 0; i < n; i++)
    {
        int a = llround(nA[i].real() / n) % mod;
        int b = llround(nB[i].real() / n) % mod;
        int c = llround(nA[i].imag() / n) % mod;
        ans[i] = (a + (b << sz) + (c << 2 * sz)) % mod;
    }
    while(ans.size() > 1 && ans.back() == 0)
        ans.pop_back();
    while(ans.size() > 100001)
        ans.pop_back();
    return ans;
}

int main() {
  
  return 0;
}