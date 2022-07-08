#include <stdio.h>

// Retarget console output7
#pragma import(__use_no_semihosting)  // 禁用半主机模式
// 请不要勾选Use MicroLib
#ifdef __MICROLIB
#error "Please do not use MicroLib!"
#endif

extern "C" {

void _sys_exit(int returncode) {
  printf("Exited! returncode=%d\n", returncode);
  while (1)
    ;
}

void _ttywrch(int ch) {}
}

namespace std {
struct __FILE {
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};

FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *stream) { return EOF; }

int fputc(int c, FILE *stream) {
  if (stream->handle == 1 || stream->handle == 2) {
    _ttywrch(c);
    return c;
  }
  return EOF;
}

int fclose(FILE *stream) { return 0; }

int fseek(FILE *stream, long int offset, int whence) { return -1; }

int fflush(FILE *stream) { return 0; }
}  // namespace std
