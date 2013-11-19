/* 
 * File:   Map.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 18:33
 */

#include "Map.h"
#include "debug.h"

void _xy(int &x, int &y, int w, int h) {
    if (x == -1) x = w - 1;
    if (y == -1) y = h - 1;
    if (x == w) x = 0;
    if (y == h) y = 0;
}

int Map::pos(int x, int y) const {
    _xy(x, y, width, height);

    return data[x + y * width];
}

void Map::set(int x, int y, int v) const {
    _xy(x, y, width, height);

    data[x + y * width] = v;
}

int Map::NextGeneration() {
    _population1 = 0;
    _population2 = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            int ret = conways_fn(i, j);

            if (ret == TILE_PLAYER1) _population1++;
            if (ret == TILE_PLAYER2 || ret == TILE_SEEN_PLAYER2) _population2++;

            buf[i + j * width] = ret;
        }

    unsigned char *tmp = data;
    data = buf;
    buf = tmp;

    return _generation++;
}

void Map::load(void* buf, int sz, int w, int h, int g) {
    if (data) free(data);
    data = (unsigned char *) buf;
    _size = sz;
    _width = w;
    _height = h;
    _generation = g;
}

void Map::save(void*& buffer, int& sz) const {
    buffer = (void *) malloc(_size);
    memcpy(buffer, data, _size);
    sz = _size;
}
