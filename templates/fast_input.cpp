#include <bits/stdc++.h>

// #define HAS_NEGATIVE_INPUT
// #define getchar getchar_unlocked

#define scanf _scanf

using InputType = int;

InputType read_one_integer() {
  char c = getchar();
  InputType ret = 0;
  
#ifdef HAS_NEGATIVE_INPUT
  bool is_negative = false;
  if (c == '-') {
    is_negative = true;
    c = getchar();
  }
#endif
  
  while (c >= '0' && c <= '9') {
    ret = ret * 10 + (c - '0');
    c = getchar();
  }
  
#ifdef HAS_NEGATIVE_INPUT
  if (is_negative) ret = -ret;
#endif
  
  return ret;
}

void _scanf(const char *format, ...) {
  // Count number of arguments;
  int cnt = 0;
  for (int i = 0; format[i]; ++i) {
    if (format[i] == '%') ++cnt;
  }
  
  va_list args;
  va_start(args, format);
  
  InputType *addr;
  while (cnt--) {
    addr = va_arg(args, InputType*);
    *addr = read_one_integer();
  }
  
  va_end(args);
}

int main() {
  
  return 0;
}
