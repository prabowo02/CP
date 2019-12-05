#include <bits/stdc++.h>
using namespace std;

struct Cuboid {
  int x, y, z, xx, yy, zz;
  
  Cuboid() {}
  
  Cuboid(int _x, int _y, int _z, int _xx, int _yy, int _zz):
    x(_x), y(_y), z(_z), xx(_xx), yy(_yy), zz(_zz) {}
    
  long long volume() {
    return 1LL * (xx - x) * (yy - y) * (zz - z);
  }
  
  Cuboid intersect(const Cuboid &other) {
    return Cuboid(
      max(x, other.x),   max(y, other.y),   max(z, other.z),
      min(xx, other.xx), min(yy, other.yy), min(zz, other.zz)
    );
  }
  
  bool operator == (const Cuboid &other) {
    return x == other.x && xx == other.xx
        && y == other.y && yy == other.yy
        && z == other.z && zz == other.zz;
  }
  
  bool valid() {
    return x < xx && y < yy & z < zz;
  }
};

ostream &operator << (ostream &os, Cuboid cuboid) {
  os << "(" << cuboid.x << ", " << cuboid.y << ", " << cuboid.z
      << ", " << cuboid.xx << ", " << cuboid.yy << ", " << cuboid.zz
      << ")";
    
  return os;
}

bool shorten(Cuboid &cuboid, Cuboid small) {
  if (cuboid.xx - cuboid.x == small.xx - small.x && cuboid.yy - cuboid.y == small.yy - small.y) {
    if (cuboid.z == small.z) {
      cuboid.z = small.zz;
      return true;
    }
    
    if (cuboid.zz == small.zz) {
      cuboid.zz = small.z;
      return true;
    }
  }
  if (cuboid.xx - cuboid.x == small.xx - small.x && cuboid.zz - cuboid.z == small.zz - small.z) {
    if (cuboid.y == small.y) {
      cuboid.y = small.yy;
      return true;
    }
    
    if (cuboid.yy == small.yy) {
      cuboid.yy = small.y;
      return true;
    }
  }
  if (cuboid.zz - cuboid.z == small.zz - small.z && cuboid.yy - cuboid.y == small.yy - small.y) {
    if (cuboid.x == small.x) {
      cuboid.x = small.xx;
      return true;
    }
    
    if (cuboid.xx == small.xx) {
      cuboid.xx = small.x;
      return true;
    }
  }
  
  return false;
}

long long f(Cuboid space, vector<Cuboid> cuboids) {
  if (!space.valid()) return 0;
 
  // cerr << space << " " << cuboids[0] << endl;
 
  if (cuboids.size() <= 6) {
    long long v = space.volume();
    for (int mask = 1; mask < 1 << cuboids.size(); mask++) {
      Cuboid intersection = space;
      for (int i=0; i<cuboids.size(); i++) {
        if (mask >> i & 1) intersection = intersection.intersect(cuboids[i]);
      }
      
      if (intersection.valid()) {
        if (__builtin_popcount(mask) & 1) v -= intersection.volume();
        else v += intersection.volume();
      }
    }
    
    return v;
  }
  
  int dx = space.xx - space.x;
  int dy = space.yy - space.y;
  int dz = space.zz - space.z;
  
  Cuboid half[2];
  
  if (dx >= dy && dx >= dz) {
    int midx = space.x + space.xx >> 1;
    half[0] = Cuboid(space.x, space.y, space.z, midx, space.yy, space.zz);
    half[1] = Cuboid(midx, space.y, space.z, space.xx, space.yy, space.zz);
  } else if (dy >= dx && dy >= dz) {
    int midy = space.y + space.yy >> 1;
    half[0] = Cuboid(space.x, space.y, space.z, space.xx, midy, space.zz);
    half[1] = Cuboid(space.x, midy, space.z, space.xx, space.yy, space.zz);
  } else {
    int midz = space.z + space.zz >> 1;
    half[0] = Cuboid(space.x, space.y, space.z, space.xx, space.yy, midz);
    half[1] = Cuboid(space.x, space.y, midz, space.xx, space.yy, space.zz);
  }
  
  long long ret = 0;
  for (int i=0; i<2; i++) {
    vector<Cuboid> nextCuboids;
    Cuboid intersection;
    
    for (Cuboid c: cuboids) {
      intersection = half[i].intersect(c);
      if (intersection.valid()) shorten(half[i], intersection); 
    }
    
    for (Cuboid c: cuboids) {
      intersection = half[i].intersect(c);
      if (intersection.valid()) nextCuboids.push_back(intersection);
    }
    ret += f(half[i], nextCuboids);
  }
  
  return ret;
}

const int MAXN = 100000;

int S[MAXN * 6];
void generateS(int n) {
  for (int i=0; i<55; i++) {
    S[i] = (300007LL * (i+1) * (i+1) * (i+1) - 200003LL * (i+1) + 100003) % 1000000;
  }
  
  for (int i=55; i<n; i++) S[i] = (S[i-24] + S[i-55]) % 1000000;
}

int solve() {
  int Mx, My, Mz, Dx, Dy, Dz, N;
  scanf("%d %d %d %d %d %d %d", &Mx, &My, &Mz, &Dx, &Dy, &Dz, &N);
  
  generateS(N * 6);
  
  vector<Cuboid> cuboids;
  for (int i=0; i<N; i++) {
    int  x = S[i*6 + 0] % Mx,  y = S[i*6 + 1] % My,  z = S[i*6 + 2] % Mz;
    int dx = S[i*6 + 3] % Dx, dy = S[i*6 + 4] % Dy, dz = S[i*6 + 5] % Dz;
    
    cuboids.push_back(Cuboid(
      x, y, z,
      x + dx + 1, y + dy + 1, z + dz + 1
    ));
  }
  
  Cuboid space = Cuboid(0, 0, 0, Mx + Dx - 1, My + Dy - 1, Mz + Dz - 1);
  
  printf("%lld\n", space.volume() - f(space, cuboids));
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
