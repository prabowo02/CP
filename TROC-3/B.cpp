#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];

int main() {
  scanf("%d", &n);
  
  int same = 0;
  for (int i=0; i<=n; i++) {
    scanf("%d", a + i);
  }
  
  for (int i=1; i<=n; i++) {
    if (a[i] == a[i-1]) ++same;
  }
  
  if (same > 1) return 0 * printf("0\n");
  if (same == 1) return 0 * printf("1\n");
  printf("%d\n", n+1);
  
  return 0;
}
