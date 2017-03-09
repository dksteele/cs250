#include <stdio.h>

int main() {
  int i;

  int *p = &i; /*instantiate int variable i and int pointer p that points to i
                  /the &i gets us the address or lvalue of i */

  i = 59;

  printf("%d\n", *p);
}
