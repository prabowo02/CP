#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  cout << max((n/a) * (m/b), (n/b) * (m/a)) << endl;
  return 0;
}
