#include <stdio.h>

int main() {
  int i, *p = &i; /*instantiate int variable i and int pointer p that points to i
                  /the &i gets us the address or lvalue of i */

  i = 43;

  printf("%d\n", *p);
}
