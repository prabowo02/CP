#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k, g1, g2, g3;
char tile[N];

vector<int> stones;

int dp[55][2][55][55];
int f(int x, int prv, int used1, int used3) {
  if (x == stones.size()) {
    int empty = n + 2 - stones.size() - used3*2 - used1;
    if (g2 < g1*2 && k > used1) {
      int left1 = k - used1;
      int extra1 = 0;
      if (left1 < empty) {
        if ((left1 & 1) && (g1 < g2)) {
          extra1 = left1-1;
        } else {
          extra1 = left1;
        }
      } else {
        extra1 = empty;
      }

      used1 += extra1;
      empty -= extra1;
    }
    
    return empty/2 * g2 + min(k, used1) * g1 + used3 * g3;
  }
  if (~dp[x][prv][used1][used3]) return dp[x][prv][used1][used3];

  int len = stones[x] - stones[x-1] - prv - 1;
  int ret = f(x+1, 0, used1 + (len & 1), used3);

  if (len > 0 && x+1 < stones.size() && stones[x+1] != stones[x] + 1) {
    ret = max(ret, f(x+1, 1, used1 + (len-1 & 1), used3 + 1));
  }

  return dp[x][prv][used1][used3] = ret;
}

int main() {
  scanf("%d %d %d %d %d", &n, &k, &g1, &g2, &g3);
  scanf("%s", tile);

  stones.push_back(-1);
  for (int i = 0; i < n; ++i) if (tile[i] == '#') stones.push_back(i);
  stones.push_back(n);

  memset(dp, -1, sizeof dp);
  printf("%d\n", f(1, 0, 0, 0));

  return 0;
}
