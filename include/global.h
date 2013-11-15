/* 
 * File:   global.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 13:25
 */

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "State.h"
#include "config.h"

#define TILE_SEEN_MASK          4

#define TILE_UNKNOWN            0
#define TILE_PLAYER1            1
#define TILE_PLAYER2            2
#define TILE_SEEN_PLAYER2       6
#define TILE_FREE               TILE_SEEN_MASK

class App {
public:
    bool loop; //cikloties un neiziet no spēlēs
    bool stats; //rādīt statistiku
    bool pause; //pauzēt spēli
    bool need_redraw; //var ir nepieciešama pārzīmēšana
    bool need_update; //vai ir nepieciešama spēles atjaunošana
    int current_fps;

    App() {
        loop = true;
        stats = true;
        pause = false;
        need_redraw = false;
        need_update = false;
        current_fps = FPS;
    };
};

extern App app;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *xsmall_font;
extern ALLEGRO_FONT *pixelette;

extern State *current_state;
extern ALLEGRO_TIMER *gps_timer;

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int x, int y,
        const char *text);
char conways_fn(int x, int y);
