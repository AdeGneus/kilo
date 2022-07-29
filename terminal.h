#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>

#define CTRL_KEY(k) ((k)&0x1f)

/* data */
typedef struct editorConfig
{
	int screenrows;
	int screencols;
	struct termios orig_termios;
} e_conf;
e_conf E;
struct termios raw;

/* terminal */
void disableRawMode(void);
void enableRawMode(void);
void die(const char *s);
char editorReadKey(void);
int getWindowSize(int *rows, int *cols);
int getCursorPosition(int *rows, int *cols);

/* input */
void editorProcessKeypress(void);

/* output */
void editorRefreshScreen(void);
void editorDrawRows(void);

/* init */
void initEditor(void);

#endif /* _TERMINAL_H_ */
