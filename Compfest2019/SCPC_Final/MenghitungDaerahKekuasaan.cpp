#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m, q;

struct BIT {
  int sum[N];
  
  void reset() {
    for (int i = 1; i < N; ++i) sum[i] = 0;
  }
  
  void update(int x) {
    for (int i = x+1; i < N; i += i & -i) {
      sum[i] += 1;
    }
  }
  
  int query(int x) {
    int ret = 0;
    for (int i = x+1; i > 0; i -= i & -i) {
      ret += sum[i];
    }
    
    return ret;
  }
} bitrow, bitcol;

int op[N];
int x[N], y[N], xx[N], yy[N];

void solve() {
  scanf("%d %d %d", &n, &m, &q);
  bitrow.reset(); bitcol.reset();

  vector<int> compX, compY;
  for (int i = 0; i < q; ++i) {
    scanf("%d", op + i);
    
    if (op[i] == 1) {
      scanf("%d", x + i);
      compX.push_back(x[i]);
    } else if (op[i] == 2) {
      scanf("%d", y + i);
      compY.push_back(y[i]);
    } else if (op[i] == 3) {
      scanf("%d %d %d %d", x+i, y+i, xx+i, yy+i);
      if (xx[i] < x[i]) swap(x[i], xx[i]);
      if (yy[i] < y[i]) swap(y[i], yy[i]);
      
      compX.push_back(xx[i]); compX.push_back(x[i] - 1);
      compY.push_back(yy[i]); compY.push_back(y[i] - 1);
      
    }
  }
  
  sort(compX.begin(), compX.end());
  compX.resize(unique(compX.begin(), compX.end()) - compX.begin());
  
  sort(compY.begin(), compY.end());
  compY.resize(unique(compY.begin(), compY.end()) - compY.begin());

  for (int i = 0; i < q; ++i) {
    if (op[i] == 1) {
      bitrow.update(lower_bound(compX.begin(), compX.end(), x[i]) - compX.begin());
    } else if (op[i] == 2) {
      bitcol.update(lower_bound(compY.begin(), compY.end(), y[i]) - compY.begin());
    } else if (op[i] == 3) {
      int row = bitrow.query(lower_bound(compX.begin(), compX.end(), xx[i]) - compX.begin()) - bitrow.query(lower_bound(compX.begin(), compX.end(), x[i] - 1) - compX.begin());
      int col = bitcol.query(lower_bound(compY.begin(), compY.end(), yy[i]) - compY.begin()) - bitcol.query(lower_bound(compY.begin(), compY.end(), y[i] - 1) - compY.begin());
      
      printf("%lld\n", 1LL * row * (yy[i]-y[i]+1) + 1LL * col * (xx[i]-x[i]+1) - 1LL * row * col);
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
