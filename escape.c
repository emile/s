/*
* escape.c - detect ANSI escape sequences
*
*       This doesn't work well without a timer or a way of detecting whether
*       the input buffer is empty. The latter approach could use kbhit() or
*       select(). This solution emits generates an ESC key before detecting
*       the ANSI code. The extra ESC is ignored in s.c.
*
*/

#include "s.h"
#include <string.h>

#define ESCBUFSZ 8
char esc_buf[ESCBUFSZ];
int esc_index = 0;

struct esc_str {
        char *seq;
        int key;
};

static struct esc_str esc_codes[] = {
        { ESCAPE_STR "[A",  KEY_UP},
        { ESCAPE_STR "[B",  KEY_DOWN},
        { ESCAPE_STR "[C",  KEY_RIGHT},
        { ESCAPE_STR "[D",  KEY_LEFT},
        { ESCAPE_STR "[6~", KEY_PGDN},
        { ESCAPE_STR "[5~", KEY_PGUP}
};
static int esc_codes_sz = sizeof(esc_codes) / sizeof(struct esc_str);

int esc_detect()
{
        int i;
        for (i = 0; i < esc_codes_sz; i++) {
                if (!strcmp(esc_codes[i].seq, esc_buf))
                        return(esc_codes[i].key);
        }
        return(0);
}

int esc_plausible()
{
        int i;
        for (i = 0; i < esc_codes_sz; i++) {
                if (!strncmp(esc_codes[i].seq, esc_buf, esc_index))
                        return(1);
        }
        return(0);
}

void esc_reset()
{
        esc_index = 0;
}

int esc_buffer(ch)
        char ch;
{
        int esc_detected;
        if (ch == ESCAPE){
                esc_buf[0] = ch;
                esc_index = 1;
                return(ch);
        }
        if (esc_index == ESCBUFSZ) { /* buffer full */
                esc_reset();
                return(ch);
        }
        if (esc_index > 0 && !esc_plausible()){
                esc_reset();
                return(ch);
        }
        if (esc_index > 0){ /* recording escape sequence */
                esc_buf[esc_index++] = ch;
                esc_buf[esc_index] = 0;
                if ((esc_detected = esc_detect()) != 0){
                        esc_reset();
                        return(esc_detected);
                } else {
                        return(0);
                }
        }
        return(ch);
}

