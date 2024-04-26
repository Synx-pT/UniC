// Copyright (C) Paul Tröster - All Rights Reserved

#include <cstdio>
#include <cstdlib>

//____________________________________________________________________________

int calc_gcd(int x, int y, bool verbose = true) {
  if (x == 0)
    return y;
  if (y == 0)
    return x;

  while (y != 0) {
    if (verbose) {
      printf("gcd(%d, %d)\n", y, x);
    }
    int temp = y;
    y = x % y;
    x = temp;
  }

  return x;
}
