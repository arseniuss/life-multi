/* 
 * File:   main.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 15:57
 */

#include <allegro5/allegro.h>
#include <cstdio>

#include "debug.h"
#include "global.h"
#include "State.h"

ALLEGRO_FONT *xsmall_font;

/* priekš fps rēķina*/
double dstart = 0;
double dend = 0;
int dcount = 0;
double fps = 0;

void draw_stats() {
    char output[1024] = {0};

    dcount++;

    if (dstart == 0) {
        dstart = dend = al_get_time();
    }
    dend = al_get_time();

    double dtime = (dend - dstart);
    if (dtime >= 1.0) {
        fps = dcount / dtime;
        dstart = dend;
        dcount = 0;
    }

    sprintf(output, "Statistics:\n    fps %f\n", fps);

    const char *state_stats = current_state->stats();

    if (state_stats) strcat(output, state_stats);

    draw_text(xsmall_font, al_map_rgb(255, 0, 0), 0, 0, output);
}
