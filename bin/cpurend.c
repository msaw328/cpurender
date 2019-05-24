#include "cpurend.h"

int cpurend_init(cpurend_t* cpr, char* name, int width, int height, int fps) {
    cpr->w = width;
    cpr->h = height;
    cpr->fps = fps;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return 1;
    }

    cpr->win = SDL_CreateWindow(
        name, 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        cpr->w,
        cpr->h,
        SDL_WINDOW_HIDDEN
    );

    if (cpr->win == NULL) {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    cpr->surf = SDL_GetWindowSurface(cpr->win);

    db_init(&(cpr->db), cpr->w, cpr->h);

    cpr->setup = NULL;
    cpr->nextframe = NULL;

    cpr->mouse_x = cpr->w / 2;
    cpr->mouse_y = cpr->h / 2;

    return 0;
}

int cpurend_run(cpurend_t* cpr) {
    if(cpr->setup == NULL || cpr->nextframe == NULL) {
        return 1;
    };

    // perform user setup
    cpr->setup(NULL, db_buf_current(&(cpr->db)), cpr->w, cpr->h, 0, 0);

    // copy the current frame from db to surface
    SDL_LockSurface(cpr->surf);
    memcpy(cpr->surf->pixels, db_buf_current(&(cpr->db)), sizeof(uint32_t) * cpr->w * cpr->h);
    SDL_UnlockSurface(cpr->surf);

    SDL_UpdateWindowSurface(cpr->win);
    db_toggle(&(cpr->db));

    SDL_ShowWindow(cpr->win);

    int quit = 0;
    SDL_Event e;

    int frame_counter = 0;
    time_t t = time(NULL);

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) { // user pressed X on window
                quit = 1;
            }

            if(e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&(cpr->mouse_x), (&(cpr->mouse_y)));
            }
        }

        cpr->nextframe(db_buf_old(&(cpr->db)), db_buf_current(&(cpr->db)), cpr->w, cpr->h, cpr->mouse_x, cpr->mouse_y);

        SDL_LockSurface(cpr->surf);
        memcpy(cpr->surf->pixels, db_buf_current(&(cpr->db)), sizeof(uint32_t) * cpr->w * cpr->h);
        SDL_UnlockSurface(cpr->surf);

        SDL_UpdateWindowSurface(cpr->win);

        frame_counter++;
        time_t t2 = time(NULL);
        if(t2 > t) {
            t = t2;
            printf("\rFPS: %d", frame_counter);
            fflush(stdout);
            frame_counter = 0;
        }
    };

    printf("\n");
    return 0;
}
