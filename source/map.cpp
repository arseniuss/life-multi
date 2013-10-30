/* 
 * File:   map.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 18:33
 */

/*
 * Funkcijas, kas apstrādā karti
 * 
 * 3
 * +---+---+----+---+---+----+---+---+---+---+----+---+---+----+---+---+
 * |000|010|11|0|010|000|0|10|010|110|000|101|11|0|000|101|0|00|010|110|
 * +----------+-----------+----------+----------+-----------+----------+               
 * 
 * 2
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |00|10|10|00|10|01|00|11|01|10|11|00|10|00|00|00|00|00|00|10|10|10|11|00|
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * 
 */

#define USED_BITS              2

/* bitu skaits kartē */
#define MAP_BITS(w, h)         (w * h * USED_BITS)
/* izmērs baitos + 1, ja ir atlikums */
#define MAP_SIZE(w, h)         (MAP_BITS(w,h)/8 + (MAP_BITS(w,h)%8?1:0))

struct Map {
    char *data;
    int w;
    int h;
};

int map_get(struct Map * map, int x, int y) {
    //TODO: debug
    int bit = y * map->h + x;
    int idx = bit / 8;
    int off = bit % 4;

    return (map->data[idx] >> (off * USED_BITS)) & 3;
}

int map_set(struct Map *map, int x, int y, int val) {
    //TODO: debug
    int bit = y * map->h + x;
    int idx = bit / 8;
    int off = bit % 4;

    map->data[idx] |= (val & 3) << (off * USED_BITS);

    return 0;
}
