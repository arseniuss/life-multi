/* 
 * File:   Map.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 18:33
 */

#include "Map.h"
#include "debug.h"

/*
 * Funkcijas, kas apstrādā karti              
 * 
 * 2
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |00|10|10|00|00|10|01|00|11|01|10|11|00|10|00|00|00|00|00|00|10|10|10|11|
 * +-----------+-----------+-----------+-----------+-----------+-----------+
 * 
 */

int Map::pos(int x, int y) const{
    return POS(data, x, y, width, height);
}

void Map::set(int x, int y, int v) const {
    SET(data, x, y, v, width, height);
}

int Map::NextGeneration() {
    _population1 = 0;
    _population2 = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            int ret = conways_fn(i, j);

            if (ret == TILE_PLAYER1) _population1++;
            if (ret == TILE_PLAYER2) _population2++;

            SET(buf, i, j, ret, width, height);
        }

    unsigned char *tmp = data;
    data = buf;
    buf = tmp;

    return _generation++;
}