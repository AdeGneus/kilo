#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

struct termios orig_termios;
struct termios raw;

void disableRawMode(void);
void enableRawMode(void);
void die(const char *s);

#endif /* _TERMINAL_H_ */
