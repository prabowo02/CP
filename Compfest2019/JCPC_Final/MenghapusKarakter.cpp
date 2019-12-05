#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k;
char s[N];

int main() {
  scanf("%d %d", &n, &k);
  scanf("%s", s);
  sort(s, s + n);

  printf("%c\n", s[k-1]);
  return 0;
}
