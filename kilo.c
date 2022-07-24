#include "terminal.h"

void die(const char *s)
{
	perror(s);
	exit(1);
}
/**
 * disableRawMode - disable terminal attributes
 *					turn on ECHO feature
 * Return: nothing
 */
void disableRawMode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}

/**
 * enableRawMode - set terminal attributes
 *					turn off some features
 * Return: nothing
 */
void enableRawMode(void)
{
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	atexit(disableRawMode);

	raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}

/**
 * main - entry point to the program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	enableRawMode();

	while (1)
	{
		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			die("read");
		read(STDIN_FILENO, &c, 1);

		if (iscntrl(c))
			printf("%d\r\n", c);
		else
			printf("%d ('%c')\r\n", c, c);

		if (c == 'q')
			break;
	}

	return (0);
}