#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int r, c;
int dance[N];

inline int d(int x, int y) {
  return dance[x*c + y];
}

int dir[N][4];

int getDir(int idx, int k) {
  if (idx == -1) return -1;
  if (dance[idx] != -1) return idx;
  return dir[idx][k] = getDir(dir[idx][k], k);
}

bool isEliminated(int x) {
  int sum = 0, cnt = 0;
  for (int k = 0; k < 4; ++k) {
    dir[x][k] = getDir(dir[x][k], k);
    if (dir[x][k] == -1) continue;
    sum += dance[dir[x][k]];
    ++cnt;
  }

  return dance[x] * cnt < sum;
}

int solve() {
  scanf("%d %d", &r, &c);
  for (int i = 0; i < r*c; ++i) {
    scanf("%d", &dance[i]);

    int x = i / c;
    int y = i % c;
    dir[i][0] = (y+1 >= c ? -1 : i+1);
    dir[i][1] = (x-1 < 0 ? -1 : i-c);
    dir[i][2] = (y-1 < 0 ? -1 : i-1);
    dir[i][3] = (x+1 >= r ? -1 : i+c);
  }

  long long ans = 0, sum = 0;
  vector<int> eliminated;
  for (int i = 0; i < r*c; ++i) {
    sum += dance[i];
    if (isEliminated(i)) {
      eliminated.push_back(i);
    }
  }

  if (eliminated.size() > 0) while (true) {
    vector<int> neliminated;
    ans += sum;
    // cerr << "sum: " << sum << endl;

    for (int i: eliminated) {
      // cerr << i/c << " " << i%c << endl;
      sum -= dance[i];
      dance[i] = -1;
    }

    for (int i: eliminated) {
      for (int k = 0; k < 4; ++k) {
        int ni = getDir(dir[i][k], k);
        if (ni != -1 && isEliminated(ni)) neliminated.push_back(ni);
      }
    }

    sort(neliminated.begin(), neliminated.end());
    neliminated.resize(unique(neliminated.begin(), neliminated.end()) - neliminated.begin());
    swap(eliminated, neliminated);

    if (eliminated.size() == 0) break;
  }
  ans += sum;

  printf("%lld\n", ans);
  return 0;
}

int main() {
  int t = 1;
  scanf("%d", &t);
  for (int tc = 0; tc < t; ++tc) {
    printf("Case #%d: ", tc+1);
    solve();
  }
  return 0;
}
