
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// contains INT_MAX
#include <limits.h>

/* return the factorial of n.
 * The result is undefined if n < 0.
 *
 * The largest factorial that can be calculated depends
 * on your platform. On platforms where a `long`
 * is 8 bytes, the results of the function for
 * any n greater than 20 are undefined.
 */
long factorial(int n) {
  long result = 1;
  for (int i = n; i > 0; i--) {
    result = result * i;
  }
  return result;
}

int main(int argc, char **argv) {
  argc--;
  argv++;

  if (argc != 1) {
    fprintf(stderr, "Error: expected 1 command-line argument (an INT), but got %d\n", argc);
    exit(1);
  }

  char *end;

  // clear errno so we can check whether strtol fails
  errno = 0;
  long n = strtol(argv[0], &end, 10);
  int res_errno = errno;

  if (end == argv[0]) {
    fprintf(stderr, "Error: couldn't interpret '%s' as a number\n", argv[0]);
    exit(1);
  } else if (res_errno == ERANGE) {
    fprintf(stderr, "Error: '%s' is outside the range of numbers we can handle\n", argv[0]);
    exit(1);
  } else if (n > INT_MAX) {
    fprintf(stderr, "Error: '%s' is too big to fit in an int\n", argv[0]);
    exit(1);
  } else if (n < 0) {
    fprintf(stderr, "Error: invalid value %ld:"
            "factorial can only be calculated for non-negative numbers\n", n);
    exit(1);
  }

  int nn = (short) n;
  long result = factorial(nn);
  printf("factorial(%d) is %ld\n", nn, result);
}
