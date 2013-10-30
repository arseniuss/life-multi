/* 
 * File:   life.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 18:29
 */

/*
 * Funkcijas, kas strādā ar spēles loģiku
 * 
 * +-+-+-+
 * |0|1|2|
 * +-+-+-+
 * |0|1|2|
 * +-+-+-+
 * |0|1|3|
 * +-+-+-+
 * 
 */

#include "debug.h"

#define TILE_FREE       0
#define TILE_WALL       3

#define TILE_PLAYER1    1
#define TILE_PLAYER2    2

typedef char part_t[3][3];

typedef char (*life_fn_t)(part_t);

//Noteikumu vertības            (tiek ||)

/** Notikums: šūna mirst */
#define RULE_DIE                        0
/** Noteikums: šūna paliek */
#define RULE_STAY                       1
/** Noteikums: tiek veidota jauna šūna */
#define RULE_CREATE                     2
/** Noteikums: tiek veidota jauna vai paliek */
#define RULE_CREATE_STAY                3

// [1. spļētāja šunas][2. spēlētāja šūnas]
// Uzmanību! Jābūt simetriskai pret x == y!
const char rules[5][5] = {
    {0, 0, 1, 3, 0},
    {0, 0, 0, 1, 1},
    {1, 0, 0, 1, 0},
    {3, 1, 1, 0, 0},
    {0, 1, 0, 0, 0}
};

/**
 * Funkcija atgriež, vai šuna, kas ir [1;1] dzīvo vai nē
 * 
 * @param map 3x3 mapes daļa
 * @return TILE_* vērtiba
 */
char conways_fn(part_t map) {
    //ja valnis -> paliek
    if (map[1][1] == TILE_WALL) return TILE_WALL;

    int x, y;
    int pl1 = 0, pl2 = 0;

    //saskaita cik ir attiecīgo spēlētāju šunas ap šo laukumu
    for (x = 0; x < 3; x++)
        for (y = 0; y < 3; y++) {
            if (x == y && x == 1) continue;
            pl1 += (map[x][y] == TILE_PLAYER1 ? 1 : 0);
            pl2 += (map[x][y] == TILE_PLAYER1 ? 1 : 0);
        }
    
    if(pl1 > 4 || pl2 > 4) return TILE_FREE;
    
    switch(rules[pl1][pl2]) {
        case RULE_DIE:
            return TILE_FREE;
        case RULE_STAY:
            return map[1][1];
        case RULE_CREATE:
            if(pl1 > pl2) return TILE_PLAYER1;
            if(pl2 < pl1) return TILE_PLAYER2;
            return TILE_FREE;
        case RULE_CREATE_STAY:
            if(pl1 > pl2) return TILE_PLAYER1;
            if(pl2 < pl1) return TILE_PLAYER2;
            return map[1][1];
    }
    
    abort("Error while processing game logic!");
    
    return 0; //:)
}
