#ifndef _CPUREND_H_
#define _CPUREND_H_

#include "doublebuf.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#define ARGB(a, r, g, b) ((a << 24) | (r << 16) | (g << 8) | b)

typedef void (func_sig_t) (uint32_t* old_frame, uint32_t* new_frame, int w, int h, int mouse_x, int mouse_y);

struct cpurend {
    int w;
    int h;
    int fps;
    SDL_Window* win;
    SDL_Surface* surf;
    doublebuf_t db;
    func_sig_t* setup;
    func_sig_t* nextframe;
    int mouse_x;
    int mouse_y;
};
typedef struct cpurend cpurend_t;

// return 1 on error, 0 ok
int cpurend_init(cpurend_t* cpr, char* name, int width, int height, int fps);

int cpurend_run(cpurend_t* cpr);

#endif
