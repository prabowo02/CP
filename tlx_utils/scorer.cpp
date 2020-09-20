#include <fstream>
#include <iostream>

std::ifstream inp;
std::ifstream out;
std::ifstream con;

void ac(std::string reason="") {
  std::cout << "AC\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void ok(double points, std::string reason="") {
  std::cout << "OK\n";
  std::cout << points;
  if (reason != "") {
    std::cout << " " << reason << '\n';
  }
  exit(0);
}

void registerScorer(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  inp = std::ifstream(argv[1]);
  out = std::ifstream(argv[2]);
  con = std::ifstream(argv[3]);
}

template<class T> inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

void eof() {
  std::string dummy;
  if (con >> dummy) wa();
}

void compareNextString() {
  std::string judge, contestant;
  readStream(out, judge); readStream(con, contestant);
  if (judge != contestant) wa();
}

void compareRemainingLines() {
  std::string judge, contestant;
  while (out >> judge) {
    readStream(con, contestant);
    if (judge != contestant) wa();
  }
  eof();
  ac();
}

double absoluteOrRelativeError(double expected, double result) {
  double absolute = (result - expected > 0 ? result - expected : expected - result);
  if ((expected > 0 ? expected : -expected) > 1e-9) {
    double relative = absolute / expected;
    if (relative < 0) relative = -relative;
    return absolute < relative ? absolute : relative;
  }
  return absolute;
}

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);
  compareRemainingLines();
}
