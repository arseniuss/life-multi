/* 
 * File:   StateGame.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 30 oktobris, 15:58
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include <cstdlib>
#include <iosfwd>

#include "Map.h"
#include "StateGame.h"
#include "config.h"
#include "debug.h"
#include "global.h"

bool button_1_down = false;
class StateGame *current_game = NULL;

#ifdef DEBUG
//priekš statistikas saglabājam peles koordinātas
int mouse_x, mouse_y;
//labot kā spēlējtājam: 1 vai 2
int debug_player = 1;
#endif

StateGame::StateGame() {
    type = STATE_GAME;
    tile_size = 30;
    tile_border = 1;

    map.create(100, 100);

    //ekrāna visus koordinātas
    int dcrx = al_get_display_width(display) / 2;
    int dcry = al_get_display_height(display) / 2;

    //Novietojam karti centrā
    scroll_x = -(map.width / 2) * (tile_size + tile_border) + dcrx;
    scroll_y = -(map.width / 2) * (tile_size + tile_border) + dcry;
    scroll_tile_x = 0;
    scroll_tile_y = 0;


    screen_map = al_create_bitmap(al_get_display_width(display),
            al_get_display_height(display));
    //cik šūnu ir ekrānā
    tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + tile_border) + 1;
    tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + tile_border) + 1;

    gps = 0.0;
}

StateGame::~StateGame() {
    al_destroy_bitmap(screen_map);
}

void StateGame::draw() {
    al_set_target_bitmap(screen_map);

    //sākt zīmēšanas saglabāšanu
    al_hold_bitmap_drawing(1);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    for (int i = scroll_tile_x; (i - scroll_tile_x) <= tile_wcount + 1 && i < map.width; i++) {
        for (int j = scroll_tile_y; (j - scroll_tile_y) <= tile_hcount + 1 && j < map.height; j++) {
            //TODO: test: varbūt piezīmēt visu ekrānu?
            int x = i * (tile_size + tile_border) + scroll_x;
            int y = j * (tile_size + tile_border) + scroll_y;

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

    //beidz zīmēšanas saglabāšanu
    al_hold_bitmap_drawing(0);

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(screen_map, 0, 0, 0);
}

void StateGame::user_key(int key) {

    switch (key) {
            //pauze
        case ALLEGRO_KEY_P:
            if (app.pause) app.pause = false;
            else app.pause = true;
            break;
    }

#ifdef DEBUG
    if (key == ALLEGRO_KEY_1) {
        debug_player = 1;
    }

    if (key == ALLEGRO_KEY_2) {
        debug_player = 2;
    }

    if (key == ALLEGRO_KEY_C) {
        map.create(map.width, map.height);
    }

    if (key == ALLEGRO_KEY_F12) {
        app.loop = false;
    }

    if (key == ALLEGRO_KEY_S) {
        this->save("test_file");
    }
    
    if(key == ALLEGRO_KEY_L) {
        this->load("test_file");
    }
#endif
}

/**
 * Kad tiek mainīts loga izmērs
 */
void StateGame::user_display() {
    //iznīcinam veco logu un izveidojam jaunu
    al_destroy_bitmap(screen_map);
    screen_map = al_create_bitmap(al_get_display_width(display),
            al_get_display_height(display));

    //pārrēķinam, cik šūnu var ievietot logā
    tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + tile_border) + 1;
    tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + tile_border) + 1;

    //pārrēķinam nobīdi
    scroll_tile_x = -scroll_x / (tile_size + tile_border) - 1;
    scroll_tile_y = -scroll_y / (tile_size + tile_border) - 1;

    if (scroll_tile_x < 0) scroll_tile_x = 0;
    if (scroll_tile_x > map.width) scroll_tile_x = map.width;

    if (scroll_tile_y < 0) scroll_tile_y = 0;
    if (scroll_tile_y > map.height) scroll_tile_y = map.height;
}

/**
 * Kad lietotājs pakustina peli
 */
void StateGame::user_mouse(int x, int y, int z, int dx, int dy, int dz) {
#ifdef DEBUG
    //saglabā priekš labošanas statistikas
    mouse_x = x;
    mouse_y = y;
#endif

    //ja tiek pārbīdīta karte
    if (button_1_down) {
        scroll_x += dx;
        scroll_y += dy;
    }

    //ja tiek mainīts kartes šūnu izmērs
    if (dz) {
        //saglabājam vecos izmērus
        int old_tile_size = tile_size;
        int old_border = tile_border;

        //veicam izmaiņas
        if (!(tile_size == MIN_TILE_SIZE && dz < 0))
            tile_size += dz;

        //pārrēķinam, cik šūnu var ietilpt logā
        tile_wcount = al_get_bitmap_width(screen_map) / (tile_size + tile_border) + 1;
        tile_hcount = al_get_bitmap_height(screen_map) / (tile_size + tile_border) + 1;

        //nobīdam karti, lai zem peles būtu tās pašas koordinātas, kas pirms
        if (dz < 0) {
            if (tile_size != MIN_TILE_SIZE) {
                scroll_x += (x - scroll_x) / (old_tile_size + old_border);
                scroll_y += (y - scroll_y) / (old_tile_size + old_border);
            }
        } else {
            scroll_x -= (x - scroll_x) / (old_tile_size + old_border);
            scroll_y -= (y - scroll_y) / (old_tile_size + old_border);
        }
    }

    scroll_tile_x = -scroll_x / (tile_size + tile_border) - 1;
    scroll_tile_y = -scroll_y / (tile_size + tile_border) - 1;

    if (scroll_tile_x < 0) scroll_tile_x = 0;
    if (scroll_tile_x > map.width) scroll_tile_x = map.width;

    if (scroll_tile_y < 0) scroll_tile_y = 0;
    if (scroll_tile_y > map.height) scroll_tile_y = map.height;
}

/**
 * Kad lietotājs paceļ peles taustiņu uz augšu
 */
void StateGame::user_mouse_up(int x, int y, int z, int dx, int dy, int dz,
        int button) {
    if (button == 1) button_1_down = false;
}

/**
 * Kad lietotājs piespiež peles taustiņu
 */
void StateGame::user_mouse_down(int x, int y, int z, int dx, int dy, int dz,
        int button) {
    //kartes pārbīdīšana
    if (button == 1) button_1_down = true;
    //jaunas šūnas izveidošana
    if (button == 2) {
        int px = (x - scroll_x) / (tile_size + tile_border);
        int py = (y - scroll_y) / (tile_size + tile_border);

#ifdef DEBUG
        switch (debug_player) {
            default:
            case 1:
                map.set(px, py, TILE_PLAYER1);
                break;
            case 2:
                if (map.pos(px, py) & TILE_SEEN_MASK)
                    map.set(px, py, TILE_SEEN_PLAYER2);
                else
                    map.set(px, py, TILE_PLAYER2);
                break;
        }
#else
        map.set(px, py, TILE_PLAYER1);
#endif
    }

}

/**
 * Nākošās ģenerācijas veidošana
 */
void StateGame::update() {
    static double gps_time1, gps_time2;
    static int gps_gen1, gps_gen2;

    gps_time2 = gps_time1;
    gps_time1 = al_get_time();
    gps_gen2 = gps_gen1;

    if (!app.pause) {
        gps_gen1 = map.NextGeneration();
    }

    //Ģenerācijas sekundē aprēķins
    gps = (gps_gen1 - gps_gen2) / (gps_time1 - gps_time2);
}

/**
 * Statistika
 */
const char *StateGame::stats() {
    static char buf[1024] = {0};
#ifdef DEBUG
    int x = (mouse_x - scroll_x) / (tile_size + tile_border);
    int y = (mouse_y - scroll_y) / (tile_size + tile_border);
    int tile = map.pos(x, y);
#endif

    sprintf(buf,
            "    scroll (%d, %d)\n"
            "    scroll_tile (%d, %d)\n"
            "    tile_size %d\n"
#ifdef DEBUG
            "    tile(%d,%d) @ %d %d = %d\n \n"
#endif
            "    generation %d.\n"
            "    gps %f\n"
            "    population 1: %d\n"
            "    population 2: %d\n \n"
            "    map %dx%d\n"
            "    map size %d (%d KB)\n",
            scroll_x, scroll_y,
            scroll_tile_x, scroll_tile_y,
            tile_size,
#ifdef DEBUG
            x, y, mouse_x, mouse_y, tile,
#endif
            map.generation,
            gps,
            map.population1,
            map.population2,
            map.width, map.height,
            map.size, map.size / 1024);

    return buf;
}

int StateGame::save(const char* filename) {
    FILE * fout;
    void * buff;
    int buf_sz;

    if (!(fout = fopen(filename, "w"))) {
        return -1;
    }

    fprintf(fout, "LifeGame v%d.%d", (APP_VERSION >> 8) & 0xFF,
            (APP_VERSION & 0xFF));

    fwrite(&scroll_x, sizeof (scroll_x), 1, fout);
    fwrite(&scroll_y, sizeof (scroll_y), 1, fout);
    fwrite(&scroll_tile_x, sizeof (scroll_tile_x), 1, fout);
    fwrite(&scroll_tile_y, sizeof (scroll_tile_y), 1, fout);

    fwrite(&tile_size, sizeof (tile_size), 1, fout);
    fwrite(&tile_border, sizeof (tile_border), 1, fout);

    fwrite(&map.width, sizeof (map.width), 1, fout);
    fwrite(&map.height, sizeof (map.height), 1, fout);
    fwrite(&map.generation, sizeof (map.generation), 1, fout);
    fwrite(&map.size, sizeof (map.size), 1, fout);

    map.save(buff, buf_sz);
    fwrite(buff, 1, buf_sz, fout);

    fclose(fout);

    return 0;
}

int StateGame::load(const char* filename) {
    FILE * fin;
    int v_upper;
    int v_lower;
    void * buff;
    int map_width;
    int map_height;
    int map_size;
    int map_generation;

    if (!(fin = fopen(filename, "r"))) {
        return -1;
    }

    fscanf(fin, "LifeGame v%d.%d", &v_upper, &v_lower);

    if (((v_upper << 8) | v_lower) != APP_VERSION) {
        debug("Unknown version %d %d!\n", v_upper, v_lower);

        return -1;
    }

    fread(&scroll_x, sizeof (scroll_x), 1, fin);
    fread(&scroll_y, sizeof (scroll_y), 1, fin);
    fread(&scroll_tile_x, sizeof (scroll_tile_x), 1, fin);
    fread(&scroll_tile_y, sizeof (scroll_tile_y), 1, fin);

    fread(&tile_size, sizeof (tile_size), 1, fin);
    fread(&tile_border, sizeof (tile_border), 1, fin);

    fread(&map_width, sizeof (map_width), 1, fin);
    fread(&map_height, sizeof (map_height), 1, fin);
    fread(&map_generation, sizeof (map_generation), 1, fin);
    fread(&map_size, sizeof (map_size), 1, fin);

    buff = malloc(map_size);
    fread(buff, map_size, 1, fin);

    map.load(buff, map_size, map_width, map_height, map_generation);

    fclose(fin);

    return 0;
}