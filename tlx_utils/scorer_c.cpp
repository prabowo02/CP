#include <cstdio>
#include <cstdlib>
#include <cstring>

FILE *inp;
FILE *out;
FILE *con;

void WA() {
  printf("WA\n");
  exit(0);
}

void AC() {
  printf("AC\n");
  exit(0);
}

int readInt(FILE *fp) {
  char buff[16];
  fscanf(fp, "%12s", buff);
  int len = strlen(buff), ret = 0;
  bool negative = buff[0] == '-';

  for (int i = (negative ? 1 : 0); i < len; ++i) {
    if (buff[i] < '0' || buff[i] > '9') WA();
    ret = ret * 10 + buff[i] - '0';
  }
  if (negative) ret *= -1;
  return ret;
}

void readString(FILE *fp, char *s) {
  fscanf(fp, "%s", s);
}

int main(int argc, char* argv[]) {
  inp = fopen(argv[1], "r");
  out = fopen(argv[2], "r");
  con = fopen(argv[3], "r");

  AC();
}
