// This is a minimalist code to convert testlib checker to
//   judgels-compatible checker with minimal changes
// Usage: replace #include "testlib.h" with everything here.
//        If there is any compile errors, they should be resolved manually

#include <bits/stdc++.h>

void ac(std::string reason="") {
  std::cout << "AC\n";
#ifdef TLX_DEBUG
  if (reason != "") {
    std::cout << reason << '\n';
  }
#endif
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
#ifdef TLX_DEBUG
  if (reason != "") {
    std::cout << reason << '\n';
  }
#endif
  exit(0);
}

void ok(double points, std::string reason="") {
  std::cout << "OK\n";
  std::cout << points;
#ifdef TLX_DEBUG
  if (reason != "") {
    std::cout << " " << reason << '\n';
  }
#endif
  exit(0);
}

enum TResult {
  _ok = 0,
  _wa = 1,
  _pe = 2,
  _fail = 3,
  _dirt = 4,
  _points = 5,
  _unexpected_eof = 8,
  _sv = 10,
  _pv = 11,
  _partially = 16
};

void quit(TResult result, std::string reason="") {
  if (result == _ok) ac(reason);
  wa(reason);
}

void quitp(double points, std::string reason="") {
  points *= 1;  // you may want to adjust this [0, 1] -> [0, 100]
  ok(points, reason);
}

void quitf(TResult result, std::string reason="", ...) {
  wa(reason);
}

template<class T>
inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

struct InStream {
  std::ifstream reader;

  void init(char *filename) {
    reader = std::ifstream(filename);
  }

  char readChar() { char ret; readStream(reader, ret); return ret; }
  int readInt() { int ret; readStream(reader, ret); return ret; }
  std::string readString() { std::string ret; readStream(reader, ret); return ret; }
  std::string readLine() { std::string ret; std::getline(reader, ret); return ret; }
  void readEof() { std::string dummy; if (reader >> dummy) wa(); }
  void readEoln() {}
  std::vector<int> readInts(int size, int minv, int maxv, std::string varname="", int index_base=1) {
    std::vector<int> ret(size);
    for (int i = 0; i < size; ++i) {
      readStream(reader, ret[i]);
      if (!(minv <= ret[i] && ret[i] <= maxv)) wa();
    }
    return ret;
  }
} inf, ans, ouf;

inline void compareNextString() {
  if (ans.readString() != ouf.readString()) wa();
}

inline void readBothSecrets(std::string secret) { compareNextString(); }
inline void readBothGraderResults() { compareNextString(); }

void registerChecker(std::string slug, int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  inf.init(argv[1]);
  ans.init(argv[2]);
  ouf.init(argv[3]);
}
