#ifndef _DOUBLEBUF_H_
#define _DOUBLEBUF_H_

#include <stdlib.h>
#include <stdint.h>

#define BUF_INDEX(x, y, w, h) (w * y + x)

struct doublebuf {
    uint32_t* buff[2];
    int current;
};
typedef struct doublebuf doublebuf_t;

int db_init(doublebuf_t* db, int w, int h);

int db_free(doublebuf_t* db);

int db_toggle(doublebuf_t* db);

uint32_t* db_buf_current(doublebuf_t* db);
uint32_t* db_buf_old(doublebuf_t* db);

#endif
