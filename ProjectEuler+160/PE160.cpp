#include <bits/stdc++.h>
using namespace std;

long long parseInt(string num, int base) {
    long long ret = 0;
    for (char c: num) {
        ret *= base;
        if (c >= '0' && c <= '9') {
            ret += c - '0';
        } else ret += c - 'A' + 10;
    }
    
    return ret;
}

string parseString(long long num, int base) {
    string ret;
    for (int i=0; i<5; i++) {
        int tmp = num % base;
        if (tmp < 10) ret += ('0' + tmp);
        else ret += ('A' + tmp - 10);
        num /= base;
    }
    
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
vector<pair<int, int>> factorize(int num) {
    vector<pair<int, int>> ret;
    for (int p: primes) {
        if (num % p) continue;
        
        int e = 0;
        do {
            e++;
            num /= p;
        } while (num % p == 0);
        
        ret.push_back({p, e});
    }
    
    return ret;
}

vector<pair<int, int>> tens;
long long b5;
vector<vector<int>> factorials;

long long factor(long long n, int p) {
    long long ret = 0;
    do {
        ret += n /= p;
    } while (n);
    return ret;
}

int power(int x, long long y, int mod) {
    long long ret = 1, mul = x;
    for (; y; y >>= 1) {
        if (y & 1) ret = ret * mul % mod;
        mul = mul * mul % mod;
    }
    return ret;
}

vector<int> num, rem;
vector<int> invNum;
int findMinX() {
    long long result = 0;
 
    for (int i = 0; i < tens.size(); i++) {
        int pp = b5 / num[i];
        result += 1LL * rem[i] * power(pp, num[i] / tens[i].first * (tens[i].first - 1) - 1, num[i]) % b5 * pp % b5;
    }
 
    return result % b5;
}

long long acc;
int noprime(int i, long long n) {
    acc = 0;
    long long ret = 1;
    for (; n; n /= tens[i].first) {
        acc += n / num[i];
        ret = ret * factorials[i][n % num[i]] % num[i];
    }
    return ret;
}

long long zeros[5];
string f(long long n, int b) {
    
    // cerr << n << " " << b << endl;    
    long long mini = n;
    for (int i=0; i<tens.size(); i++) {
        zeros[i] = ( factor(n, tens[i].first) );
        mini = min(mini, zeros[i] / tens[i].second);
    }
    
    rem.clear();
    for (int i=0; i<tens.size(); i++) {
        long long res = noprime(i, n);
        res = res * power(factorials[i][num[i]], acc, num[i]) % num[i];
        
        for (int j=0; j<tens.size(); j++) {
            if (i == j) continue;
            
            res = res * power(power(tens[j].first, num[i] / tens[i].first * (tens[i].first - 1) - 1, num[i]), zeros[j], num[i]) % num[i];
        }
        
        rem.push_back(res);
    }
    
    for (int i=0; i<tens.size(); i++) {
        zeros[i] -= mini * tens[i].second;
    }
    
    long long ret = findMinX();
    
    for (int i=0; i<tens.size(); i++) {
        ret = ret * power(tens[i].first, zeros[i], b5) % b5;
    }
    
    return parseString(ret, b);
}

int main() {
    // clock_t t = clock();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int b, q;
    string n;
    cin >> b >> q;
    
    tens = factorize(b);
    b5 = b * b * b * b * b;
    
    for (int i=0; i<tens.size(); i++) {
        int p = 1;
        for (int j=0; j<tens[i].second; j++)
            p *= tens[i].first;
        
        int p5 = p * p * p * p * p;
        
        factorials.push_back(vector<int>(p5 + 1));
        factorials.back()[0] = 1;
        for (int i=1; i<=p5; i++) factorials.back()[i] = i;
        for (int j=tens[i].first; j<=p5; j+=tens[i].first) factorials.back()[j] = 1;
        for (int i=1; i<=p5; i++) factorials.back()[i] = 1LL * factorials.back()[i] * factorials.back()[i-1] % p5;
        
        num.push_back(p5);
    }
    
    while (q--) {
        cin >> n;
        cout << f(parseInt(n, b), b) << '\n';
    }
    // cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
