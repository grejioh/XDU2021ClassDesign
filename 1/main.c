#include <stdio.h>
#include <string.h>
const int LEN = 10000;
int a[LEN], b[LEN], c[LEN];
void read(int *a) {
  char s[LEN + 1];
  scanf("%s", s);

  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    a[len - i - 1] = s[i] - '0';
  }
}
void print(int *a) {
  int flag = 0; // find first nonzero
  for (int i = LEN - 1; i >= 0; i--) {
    if (a[i] == 0 && flag == 0) {
      continue;
    } else {
      flag = 1;
      printf("%d", a[i]);
    }
  }
}
void add(int *a, int *b, int *c) {
  for (int i = 0; i < LEN; i++) {
    c[i] += a[i] + b[i];
    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10;
      c[i] = c[i] % 10;
    }
  }
}
int main() {
  read(a);
  read(b);
  add(a, b, c);
  print(c);
  return 0;
}
