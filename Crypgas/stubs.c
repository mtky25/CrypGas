#include <stdlib.h>
#include <sys/stat.h>

extern unsigned char heap_svr;
static unsigned char *heap_end = &heap_svr;

void *_sbrk(int incr) {
    unsigned char *prev = heap_end;
    heap_end += incr;
    return prev;
}

int _close(int file) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file) {
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
    while (1) { /* loop infinito */ }
}

void _kill(int pid, int sig) {
  // Não faz nada
}

int _getpid(void) {
  return 1;
}

int _open(const char *name, int flags, int mode) {
  return -1;
}

// Ajuste aqui: retorne len para simular escrita bem-sucedida
int _write (int file, char * ptr, int len) {
  return len;
}

// Retorne 0 para EOF ou -1 para erro
int _read (int file, char * ptr, int len) {
  return 0;
}

int _gettimeofday(struct timeval *tv, void *tzvp) {
    if (tv) {
        tv->tv_sec = 0;
        tv->tv_usec = 0;
    }
    return 0;
}