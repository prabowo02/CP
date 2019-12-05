#include <bits/stdc++.h>
using namespace std;

int r, c, n;

int horizontal[10] = {2, 0, 3, 3, 1, 3, 3, 1, 3, 3};
int vertical[10] = {4, 2, 2, 2, 3, 2, 3, 2, 4, 3};
int points[10] = {2, 3, 0, 0, 3, 0, 0, 2, 0, 0};

int main() {
  scanf("%d %d %d", &c, &r, &n);

  int hsum = 0, vsum = 0, psum = 0, dsum = 0;

  int tmpN = n;
  while (n > 0) {
    int d = n % 10;
    n /= 10;

    hsum += horizontal[d];
    vsum += vertical[d];
    psum += points[d];
    ++dsum;
  }
  n = tmpN;

  int ans = -1;
  int w = -1, h = -1, t = -1;
  for (int thickness = 1; ; ++thickness) {
    int min_height = thickness * 3 + 2;
    int min_width = thickness * 2 + 1;

    int min_balloon = min_width * thickness * hsum + thickness * thickness * psum + thickness * vsum;
    if (min_balloon > n || min_height > r || min_width*dsum + dsum-1 > c) break;

    for (int height = min_height; ; height += 2) {
      int balloon = min_balloon + (height - min_height) * thickness * vsum;
      if (balloon > n || height > r) break;

      int balloon_left = n - balloon;
      int additional_width = min(balloon_left / (hsum * thickness), (c - (min_width*dsum + dsum-1)) / dsum);

      balloon_left -= additional_width * hsum * thickness;

      if (n - balloon_left > ans) {
        ans = n - balloon_left;
        w = min_width + additional_width;
        h = height;
        t = thickness;
      }
    }
  }

  if (ans == -1) return 0 * printf("-1\n");

  printf("%d %d %d\n", w, h, t);
  return 0;
}
