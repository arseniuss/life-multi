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

StateGame::StateGame() {
    type = STATE_GAME;
    tile_size = 30;

    map.create(255, 255);

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

            al_draw_filled_rectangle(x, y, x + tile_size, y + tile_size,
                    al_map_rgb(rand() % 255, rand() % 40, rand() % 2));
            al_draw_textf(xsmall_font, al_map_rgb(0, 0, 0), x, y, 0, "%d;%d", i, j);
        }
    }

    al_hold_bitmap_drawing(0);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(screen_map, 0, 0, 0);
}

void StateGame::user_key(int key) {
    if (key == ALLEGRO_KEY_ESCAPE) {
        app.pause = true;
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

}

const char *StateGame::stats() {
    static char buf[1024] = {0};

    sprintf(buf,
            "    scroll (%d, %d)\n"
            "    scroll_tile (%d, %d)\n"
            "    tile_size %d\n",
            scroll_x, scroll_y,
            scroll_tile_x, scroll_tile_y,
            tile_size);

    return buf;
}
