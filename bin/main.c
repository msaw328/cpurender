#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <math.h>

#include "cpurend.h"
#include "doublebuf.h"

#define WIDTH 640
#define HEIGHT 480
#define FPS 60

// setup is used to create first frame before the animation is even running, so old_frame is NULL
// and mouse_x and mosue_y are 0, everythign else is usable
void setup(uint32_t* old_frame, uint32_t* new_frame, int w, int h, int mouse_x, int mouse_y) {
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            int i = BUF_INDEX(x, y, w, h);
            new_frame[i] = ARGB(255, 0, 0, 0);
        }
    }
}

void nextframe(uint32_t* old_frame, uint32_t* new_frame, int w, int h, int mouse_x, int mouse_y) {
    uint32_t color;

    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {

            double dist = sqrt((double) ((mouse_x - x) * (mouse_x - x) + (mouse_y - y) * (mouse_y - y)));

            double radius = 100.0;
            int fill;
            if(dist >= radius) {
                fill = 255;
            } else {
               fill = (int) ((dist / radius) * 255.0);
            }

            // invert circle
            fill = 255 - fill;

            color = ARGB(255, fill, fill, fill);

            int i = BUF_INDEX(x, y, w, h);
            new_frame[i] = color;
        }
    }
}

int main(int argc, char** argv) {
    cpurend_t cpr;
    cpurend_init(&cpr, "HELLO WORLD", WIDTH, HEIGHT, FPS);
    cpr.setup = &setup;
    cpr.nextframe = &nextframe;
    cpurend_run(&cpr);
}
