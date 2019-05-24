#include "doublebuf.h"

int db_init(doublebuf_t* db, int w, int h) {
    db->current = 0;

    db->buff[0] = malloc(sizeof(uint32_t) * w * h);
    db->buff[1] = malloc(sizeof(uint32_t) * w * h);

    return 0;
}

int db_free(doublebuf_t* db) {
    free(db->buff[0]);
    free(db->buff[1]);

    return 0;
}


int db_toggle(doublebuf_t* db) {
    db->current ^= 1; // toggles between 0 and 1

    return 0;
}

uint32_t* db_buf_current(doublebuf_t* db) {
    return db->buff[db->current];
}

uint32_t* db_buf_old(doublebuf_t* db) {
    return db->buff[db->current ^ 1];
}
