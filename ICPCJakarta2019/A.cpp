#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    printf("%d ", n - a[i] + 1);
  }
  printf("\n");
  return 0;
}
