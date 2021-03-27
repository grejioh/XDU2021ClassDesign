#include <stdio.h>
#include <string.h>
const int LEN = 10000;
int a[LEN], b[LEN];
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
int main() {
  read(a);
  print(a);
  return 0;
}
