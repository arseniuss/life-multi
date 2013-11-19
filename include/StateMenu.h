/* 
 * File:   StateMenu.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 14:43
 */

#pragma once

#ifdef __cplusplus

#include <allegro5/allegro.h>

#include "State.h"

#define MENU_ENTRIES                    4

#define MENU_NEW_GAME                   0
#define MENU_STATISTICS                 1
#define MENU_OPTIONS                    2
#define MENU_CREADITS                   3

const char * const menu_entry[MENU_ENTRIES] = {
        "New Game",
        "Statistics",
        "Options",
        "Credits"
};

class StateMenu : public State {
private:
    int current_menu;
public:
    typedef State super;

    StateMenu();
    void draw();
    void user_key(int key);
};

#endif