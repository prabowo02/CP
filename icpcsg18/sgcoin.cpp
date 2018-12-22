#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long H(long long previousHash, string &transaction,
            long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

string s = "icpcsg2018";
long long nextToken(long long h) {
  long long ret = H(h, s, 0);
  
  if (ret >= 1000000000) return MOD - ret;
  return 10000000 - ret % 10000000;
}

int main() {
  
  long long h;
  scanf("%lld", &h);
  
  long long tok = nextToken(h);
  cout << s << " " << tok << endl;
  // cerr << H(h, s, tok) << endl;
  
  h = H(h, s, tok);
  tok = nextToken(h);
  cout << s << " " << tok << endl;
  // cerr << H(h, s, tok) << endl;
  
  return 0;
}
