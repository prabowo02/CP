#include <bits/stdc++.h>
using namespace std;

const int N = 2000005;

int factors[N], pcount[N];

int main() {
  clock_t t = clock();
  for (int i=1; i<N; i++) factors[i] = 1;
  
  for (int i=2; i<N; i++) {
    if (pcount[i] == 0) {
      for (int j=i; j<N; j+=i) {
        int tmp = j;
        int e = 0;
        do {
          tmp /= i;
          ++e;
        } while (tmp % i == 0);
        
        factors[j] *= e + 1;
        ++pcount[j];
      }
    }
  }
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  
  int q;
  scanf("%d", &q);
  while (q--) {
    int n;
    scanf("%d", &n);
    printf("%d\n", factors[n] - pcount[n]);
  }
  return 0;
}
