/* 
 * File:   StateMenu.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 14:49
 */

#include <allegro5/allegro.h>
#include <cstdlib>

#include "State.h"
#include "StateMenu.h"
#include "debug.h"
#include "global.h"
#include "StateGame.h"

ALLEGRO_FONT *pixelette;

StateMenu::StateMenu() {
    this->type = STATE_SIMPLE;
    current_menu = 0;
}

void StateMenu::draw() {
    ALLEGRO_COLOR c;
    ;

    for (int i = 0; i < MENU_ENTRIES; i++) {
        if (i == current_menu) {
            c = al_map_rgb(rand() % 256, 0, 0);
        } else {
            c = al_map_rgb(255, 0, 0);
        }
        al_draw_text(pixelette, c,
                al_get_display_width(display) / 2,
                (al_get_display_height(display) / 2) -
                al_get_font_line_height(pixelette) * (MENU_ENTRIES / 2) +
                al_get_font_line_height(pixelette) * i,
                ALLEGRO_ALIGN_CENTRE, menu_entry[i]);
    }
}

void StateMenu::user_key(int key) {
    switch (key) {
        case ALLEGRO_KEY_ESCAPE:
            app.loop = false; //exit program
            break;
        case ALLEGRO_KEY_UP:
            if (current_menu > 0) current_menu--;
            else current_menu = MENU_ENTRIES - 1;
            break;
        case ALLEGRO_KEY_DOWN:
            if (current_menu < MENU_ENTRIES - 1) current_menu++;
            else current_menu = 0;
            break;
        case ALLEGRO_KEY_ENTER:
            switch (current_menu) {
                case MENU_NEW_GAME:
                    current_game = new StateGame;
                    current_state = current_game;
                    
                    this->~StateMenu();
                    break;
                default:
                    debug("Unimplemented menu entry!\n");
                    break;
            }
            break;
        default:
            debug("Unknown key (%d) for state menu!\n", key);
            break;
    }
}
