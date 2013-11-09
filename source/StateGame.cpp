/* 
 * File:   StateGame.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 30 oktobris, 15:58
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>

#include "Map.h"
#include "StateGame.h"
#include "debug.h"
#include "global.h"
#include "config.h"

bool button_1_down = false;
class StateGame *current_game = NULL;

#ifdef DEBUG
int mouse_x, mouse_y;
int debug_player = 1;
#endif

StateGame::StateGame() : map(_map) {
    type = STATE_GAME;
    tile_size = 30;

    _map.create(512, 512);

    scroll_x = 0;
    scroll_y = 0;
    scroll_tile_x = 0;
    scroll_tile_y = 0;

    screen_map = al_create_bitmap(al_get_display_width(display),
            al_get_display_height(display));
    tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + 1) + 1;
    tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + 1) + 1;
}

StateGame::~StateGame() {
    al_free(screen_map);
}

void StateGame::draw() {
    al_set_target_bitmap(screen_map);

    al_hold_bitmap_drawing(1);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    for (int i = scroll_tile_x; (i - scroll_tile_x) <= tile_wcount + 1 && i < map.width; i++) {
        for (int j = scroll_tile_y; (j - scroll_tile_y) <= tile_hcount + 1 && j < map.height; j++) {
            int x = i * (tile_size + 1) + scroll_x;
            int y = j * (tile_size + 1) + scroll_y;

            int pos = map.pos(i, j);

            switch (pos) {
                case TILE_UNKNOWN:
                    al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size, al_map_rgb(10, 10, 10));
                    break;
                case TILE_FREE:
                    al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size, al_map_rgb(50, 50, 50));
                    break;
                case TILE_PLAYER1:
                    al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size, al_map_rgb(0, 255, 0));
                    break;
                case TILE_PLAYER2:
                    al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size, al_map_rgb(100, 10, 100));
                    break;
                case TILE_SEEN_PLAYER2:
                    al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size, al_map_rgb(255, 0, 0));
                    break;
            }


            //al_draw_textf(xsmall_font, al_map_rgb(0, 0, 0), x, y, 0, "%d;%d", i, j);
        }
    }

    al_hold_bitmap_drawing(0);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(screen_map, 0, 0, 0);
}

void StateGame::user_key(int key) {
    if (key == ALLEGRO_KEY_P) {
        if (app.pause) app.pause = false;
        else app.pause = true;
    }

    if (key == ALLEGRO_KEY_1) {
        debug_player = 1;
    }

    if (key == ALLEGRO_KEY_2) {
        debug_player = 2;
    }
}

void StateGame::user_display() {
    al_free(screen_map);
    screen_map = al_create_bitmap(al_get_display_width(display),
            al_get_display_height(display));

    tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + 1) + 1;
    tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + 1) + 1;

    scroll_tile_x = -scroll_x / (tile_size + 1) - 1;
    scroll_tile_y = -scroll_y / (tile_size + 1) - 1;

    if (scroll_tile_x < 0) scroll_tile_x = 0;
    if (scroll_tile_x > map.width) scroll_tile_x = map.width;

    if (scroll_tile_y < 0) scroll_tile_y = 0;
    if (scroll_tile_y > map.height) scroll_tile_y = map.height;
}

void StateGame::user_mouse(int x, int y, int z, int dx, int dy, int dz) {
#ifdef DEBUG
    mouse_x = x;
    mouse_y = y;
#endif

    if (button_1_down) {
        scroll_x += dx;
        scroll_y += dy;
    }

    if (dz) {
        if (!(tile_size == MIN_TILE_SIZE && dz < 0))
            tile_size += dz;
        tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + 1) + 1;
        tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + 1) + 1;
    }

    scroll_tile_x = -scroll_x / (tile_size + 1) - 1;
    scroll_tile_y = -scroll_y / (tile_size + 1) - 1;

    if (scroll_tile_x < 0) scroll_tile_x = 0;
    if (scroll_tile_x > map.width) scroll_tile_x = map.width;

    if (scroll_tile_y < 0) scroll_tile_y = 0;
    if (scroll_tile_y > map.height) scroll_tile_y = map.height;
}

void StateGame::user_mouse_up(int x, int y, int z, int dx, int dy, int dz,
        int button) {
    if (button == 1) button_1_down = false;
}

void StateGame::user_mouse_down(int x, int y, int z, int dx, int dy, int dz,
        int button) {
    if (button == 1) button_1_down = true;
    if (button == 2) {
        int x = (mouse_x - scroll_x) / (tile_size + 1);
        int y = (mouse_y - scroll_y) / (tile_size + 1);

        switch (debug_player) {
            default:
            case 1:
                map.set(x, y, TILE_PLAYER1);
                break;
            case 2:
                if (map.pos(x, y) & TILE_SEEN_MASK)
                    map.set(x, y, TILE_SEEN_PLAYER2);
                else
                    map.set(x, y, TILE_PLAYER2);
                break;
        }
    }

}

double gps_time1, gps_time2;
int gps_gen1, gps_gen2;

void StateGame::update() {
    gps_time2 = gps_time1;
    gps_time1 = al_get_time();
    gps_gen2 = gps_gen1;

    if (!app.pause) {
        gps_gen1 = _map.NextGeneration();
    }
}

const char *StateGame::stats() {
    static char buf[1024] = {0};

    int x = (mouse_x - scroll_x) / (tile_size + 1);
    int y = (mouse_y - scroll_y) / (tile_size + 1);
    int tile = map.pos(x, y);

    sprintf(buf,
            "    scroll (%d, %d)\n"
            "    scroll_tile (%d, %d)\n"
            "    tile_size %d\n"
            "    tile(%d,%d) = %d\n \n"
            "    generation %d.\n"
            "    gps %f\n"
            "    population 1: %d\n"
            "    population 2: %d\n \n"
            "    map %dx%d\n"
            "    map size %d (%f KB)\n",
            scroll_x, scroll_y,
            scroll_tile_x, scroll_tile_y,
            tile_size,
            x, y, tile,
            map.generation,
            (gps_gen1 - gps_gen2) / (gps_time1 - gps_time2),
            map.population1,
            map.population2,
            map.width, map.height,
            map.size, map.size / 1024.0);

    return buf;
}
