/* 
 * File:   global.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 13:25
 */

#pragma once

#include <allegro5/allegro.h>

class App {
public:
    bool loop;

    App() : loop(true) {
    };
};

extern App app;

extern ALLEGRO_DISPLAY *display;
