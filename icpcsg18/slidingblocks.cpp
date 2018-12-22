#include <bits/stdc++.h>
using namespace std;

const int N = 400005;

int n, m, b;
int x[N], y[N];

pair<int, int> initial;
set<pair<int, int>> blocks;

set<int> xs[N], ys[N];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
int getDegree(pair<int, int> p) {
  int x = p.first, y = p.second;
  
  int ret = 0;
  for (int i=0; i<4; i++) {
    if (blocks.find({x + dx[i], y + dy[i]}) != blocks.end()) ++ret;
  }
  
  return ret;
}

int getNeighborDirection(pair<int, int> p) {
  int x = p.first, y = p.second;
  
  for (int i=0; i<4; i++) {
    if (blocks.find({x + dx[i], y + dy[i]}) != blocks.end()) return i;
  }
  
  return -1;
}

bool isDirectionBoundary(pair<int, int> p, int dir) {
  int x = p.first, y = p.second;
  
  if (dir == 0) {
    if (*ys[x].begin() == y) return true;
    return false;
  }
  
  if (dir == 1) {
    if (*xs[y].rbegin() == x) return true;
    return false;
  }
  
  if (dir == 2) {
    if (*ys[x].rbegin() == y) return true;
    return false;
  }
  
  if (dir == 3) {
    if (*xs[y].begin() == x) return true;
    return false;
  }
  
  return false;
}

char getCharDirection(int dir) {
  if (dir == 0) return '>';
  if (dir == 1) return '^';
  if (dir == 2) return '<';
  if (dir == 3) return 'v';
  return '?';
}

void push_ans(vector<pair<char, int>> &ans, pair<int, int> p, int dir) {
  if (dir == 0 || dir == 2) {
    ans.push_back({getCharDirection(dir), p.first});
  } else if (dir == 1 || dir == 3) {
    ans.push_back({getCharDirection(dir), p.second});
  }
}

void removeBlock(pair<int, int> p) {
  int x = p.first, y = p.second;

  blocks.erase(p);
  xs[y].erase(x);
  ys[x].erase(y);
}

vector<pair<int, int>> next_blocks(pair<int, int> p) {
  int x = p.first, y = p.second;
  vector<pair<int, int>> ret;
  
  if (xs[y].size() > 0) {
    ret.push_back({*xs[y].begin(), y});
    if (xs[y].size() > 1) ret.push_back({*xs[y].rbegin(), y});
  }
  
  if (ys[x].size() > 0) {
    ret.push_back({x, *ys[x].begin()});
    if (ys[x].size() > 1) ret.push_back({x, *ys[x].rbegin()});
  }
  
  return ret;
}

int main() {
  scanf("%d %d %d", &n, &m, &b);
  for (int i=0; i<b; i++) {
    scanf("%d %d", x + i, y + i);
    
    blocks.insert({x[i], y[i]});
    xs[y[i]].insert(x[i]);
    ys[x[i]].insert(y[i]);
  }
  
  initial = {x[0], y[0]};
  
  vector<pair<char, int>> ans;
  
  queue<pair<int, int>> q;
  for (int i=1; i<b; i++) {
    pair<int, int> p = {x[i], y[i]};
    if (getDegree(p) == 1) {
      int dir = getNeighborDirection(p);
      
      if (isDirectionBoundary(p, dir)) {
        q.push(p);
        removeBlock(p);
        push_ans(ans, p, dir);
      }
    }
  }
  
  while (q.size()) {
    pair<int, int> p = q.front();
    q.pop();
    
    for (pair<int, int> np: next_blocks(p)) {
      if (np == initial) continue;
      
      if (getDegree(np) == 1) {
        int dir = getNeighborDirection(np);
        
        if (isDirectionBoundary(np, dir)) {
          q.push(np);
          removeBlock(np);
          push_ans(ans, np, dir);
        }
      }
    }
  }
  
  if (ans.size() != b - 1) return 0 * printf("impossible\n");
  
  reverse(ans.begin(), ans.end());
  
  printf("possible\n");
  for (int i=0; i<ans.size(); i++) {
    printf("%c %d\n", ans[i].first, ans[i].second);
  }
  
  return 0;
}
