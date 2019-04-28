#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int p, q;
int crepe(int a[]) {
  int ret = 0;
  int maks = 0;
  
  int cur = 0;
  for (int i=0; i<=q; i++) {
    cur += a[i];
    if (cur > maks) {
      maks = cur;
      ret = i;
    }
  }
  
  return ret;
}

int vert[N], hori[N];
int solve() {
  
  scanf("%d %d", &p, &q);
  for (int i=0; i<=q; i++) vert[i] = hori[i] = 0;
  
  for (int i=0; i<p; i++) {
    int x, y;
    char c;
    scanf("%d %d %c", &x, &y, &c);
    getchar();
    
    if (c == 'N') {
      vert[y+1]++;
    } else if (c == 'S') {
      vert[0]++;
      vert[y]--;
    } else if (c == 'E') {
      hori[x+1]++;
    } else {
      hori[0]++;
      hori[x]--;
    }
  }
  
  printf("%d %d\n", crepe(hori), crepe(vert));
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tc=0; tc<t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
