#include "String.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

// generate a random string
char *randomString(int len = 100) {
  const int asciiStart = 32; // Start of ASCII characters
  const int asciiEnd = 126;  // End of ASCII characters
  const int asciiRange = asciiEnd - asciiStart + 1;

  char *result = new char[len + 1];

  for (int i = 0; i < len; i++) {
    int randomNum = lrand48();
    result[i] = static_cast<char>(asciiStart + (randomNum % asciiRange));
  }

  // Null-terminate the string
  result[len] = '\0';

  return result;
}

void performanceTest() {
  // Amount of random Strings.
  int n = 10000;

  StringSorter o1(n);
  StringSorter o2(n);

  for (int i = 0; i < n; i++) {
    char *randomStr = randomString();
    o1[i] = randomStr;
    o2[i] = randomStr;
  }
  // Test Copy
  clock_t start = clock();
  o1.sortWithCopy();
  clock_t end = clock();

  float elapsed_time = 1.0 * (end - start) / CLOCKS_PER_SEC;
  printf("%.2f seconds\n", elapsed_time);

  // Test Move
  clock_t start2 = clock();
  o2.sortWithMove();
  clock_t end2 = clock();

  float elapsed_time2 = 1.0 * (end2 - start2) / CLOCKS_PER_SEC;
  printf("%.2f seconds\n", elapsed_time2);
}

int main() {
  performanceTest();

  return 0;
}
