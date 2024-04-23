
#include <cstdio>
#include <cstdlib>

int calc_gcd(int x, int y, bool verbose = false) {
  if (x == 0)
    return y;
  if (y == 0)
    return x;

  while (y != 0) {
    if (verbose) {
      printf("gcd(%d, %d)\n", x, y);
    }
    int temp = y;
    y = x % y;
    x = temp;
  }

  return x;
}
