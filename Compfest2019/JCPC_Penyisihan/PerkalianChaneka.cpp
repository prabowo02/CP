#include <bits/stdc++.h>
using namespace std;

long long a, b;

int main() {
  scanf("%lld %lld", &a, &b);
  if (a % 11 == 0) a /= 11;
  else if (b % 11 == 0) b /= 11;
  
  printf("%lld\n", a * b);
  return 0;
}
