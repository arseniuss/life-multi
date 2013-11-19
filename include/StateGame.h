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
    double gps;
    int _current_gps;
    
    int scroll_x, scroll_tile_x;
    int scroll_y, scroll_tile_y;
    ALLEGRO_BITMAP *screen_map;
    
    int tile_size;
    int tile_border;
    int tile_wcount;
    int tile_hcount;
    
    ALLEGRO_TIMER *gps_timer;
public:
    const int &current_gps;
    
    Map map;
    StateGame();
    ~StateGame();
    void draw();
    void update();
    void user_key(int key);
    void user_display();
    void user_mouse(int x, int y, int z, int dx, int dy, int dz);
    void user_mouse_down(int x, int y, int z, int dx, int dy, int dz, int button);
    void user_mouse_up(int x, int y, int z, int dx, int dy, int dz, int button);
    const char * stats();
    int save(const char *filename);
    int load(const char *filename);
};

extern class StateGame *current_game;
