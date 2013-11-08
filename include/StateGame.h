/* 
 * File:   StateGame.h
 * Author: arseniuss
 *
 * Created on trešdiena, 2013, 30 oktobris, 15:54
 */

#pragma once

#include "Map.h"
#include "State.h"

class StateGame : public State {
private:
    int generation;
    Map map;

    int scroll_x, scroll_tile_x;
    int scroll_y, scroll_tile_y;
    ALLEGRO_BITMAP *screen_map;
    int tile_size;
    int tile_wcount;
    int tile_hcount;
public:
    StateGame();
    ~StateGame();
    void draw();
    void user_key(int key);
    void user_display();
    void user_mouse(int x, int y, int z, int dx, int dy, int dz);
    void user_mouse_down(int x, int y, int z, int dx, int dy, int dz, int button);
    void user_mouse_up(int x, int y, int z, int dx, int dy, int dz, int button);
    const char * stats();
};
