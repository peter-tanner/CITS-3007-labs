
#include <stdlib.h>
#include <stdio.h>

#define STR_BUF_SIZE 1024

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define CHECK_ALLOC(block)                                   \
  if (block == 0)                                            \
  {                                                          \
    printf("malloc() failed at " STR(__LINE__) ". Exited."); \
    exit(-1);                                                \
  }

int main(void)
{
  char *buf;
  buf = malloc(STR_BUF_SIZE); // allocate a large buffer
  CHECK_ALLOC(buf)

  printf("type some text and hit 'return':\n");
  fgets(buf, STR_BUF_SIZE, stdin); // read 1024 chars into buf
  printf("\n%s\n\n", buf);         // print what was entered
  free(buf);
  return 0;
}
