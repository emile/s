/*
* s.h - macro definitions for the screen editor
*/
#include <stdio.h>
#include <ctype.h>

#define CR		'\r'		/* sent by <return> key */
#define ctrl(x)		(x & 037)	/* control character 'x' */
#define ESCAPE		27		/* end-of-insertion character */
#define BACKSPACE	127		/* backspace keycode */
#define ESCAPE_STR	"\033"		/* ANSI escape sequence init */
#define MAXTEXT		1000		/* maximum length of a line */
#define SCROLL_SIZE	12		/* number of rows to scroll */
#define TAB_WIDTH	8		/* columns per tab character */

#define abs(x)		((x > 0) ? x : -(x))
#define max(x,y)	(x > y) ? x : y
#define min(x,y)	(x < y) ? x : y

/* for an unknown command, ring the bell */
#define UNKNOWN  putc(7, stderr)

#define NCOL		80	/* columns per screen row */
#define NROW		24	/* rows per screen */

#define REDRAW          (-100)
#define KEY_UP          (-101)
#define KEY_DOWN        (-102)
#define KEY_RIGHT       (-103)
#define KEY_LEFT        (-104)
#define KEY_PGUP        (-105)
#define KEY_PGDN        (-106)
#define ISKEY(K)        ((K) >= -106 && (K) <= -100)

