/* 
 * File:   main.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 114:49
 */

#include <allegro5/allegro.h>
#include <cstdlib>

#include "State.h"
#include "StateMenu.h"
#include "debug.h"
#include "global.h"

StateMenu::StateMenu() {
    this->type = STATE_SIMPLE;
}

void StateMenu::draw() {
    return;
}

void StateMenu::user_key(int key) {
    switch (key) {
        case ALLEGRO_KEY_ESCAPE:
            app.loop = false; //exit program
            break;
        case ALLEGRO_KEY_UP:
            break;
        case ALLEGRO_KEY_DOWN:
            break;
        case ALLEGRO_KEY_RIGHT:
            break;
        case ALLEGRO_KEY_LEFT:
            break;
        case ALLEGRO_KEY_ENTER:
            break;
        default:
            debug("Unknown key (%d) for state menu!\n", key);
            break;
    }
}
