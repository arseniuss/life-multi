/* 
 * File:   global.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 13:25
 */

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class App {
public:
    bool loop;
    bool stats;

    App() {
        loop = true; //cikloties un neiziet no spēlēs
        stats = true; //rādīt statistiku
    };
};

extern App app;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *xsmall_font;

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y,
        const char *text);


