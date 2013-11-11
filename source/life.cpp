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
#include "global.h"
#include "Map.h"
#include "StateGame.h"

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
 * @return TILE_* vērtiba
 */
char conways_fn(int x, int y) {
    int pl1 = 0, pl2 = 0;

    //saskaita cik ir attiecīgo spēlētāju šunas ap šo laukumu
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (i == j && j == 0) continue;

            switch (current_game->map.pos(x + i, y + j)) {
                case TILE_PLAYER1: pl1++;
                    break;
                case TILE_SEEN_PLAYER2:
                case TILE_PLAYER2: pl2++;
                    break;

            }
        }

    int pos = current_game->map.pos(x, y);

    if (pl1 > 4) return TILE_FREE;
    if (pl2 > 4) {
        if (pos == TILE_SEEN_PLAYER2 || pos == TILE_FREE || pos == TILE_PLAYER1)
            return TILE_FREE;
        else
            return TILE_UNKNOWN;
    }


    switch (rules[pl1][pl2]) {
        case RULE_DIE:
            if (pl1 > 0) return TILE_FREE;
            if (pos == TILE_PLAYER1) return TILE_FREE;
            if (pos == TILE_SEEN_PLAYER2) return TILE_FREE;
            if (pos == TILE_FREE) return TILE_FREE;
            return TILE_UNKNOWN;
        case RULE_STAY:
            if (pl1 > 0 && pos == TILE_UNKNOWN) return TILE_FREE;
            if (pl1 > 0 && pos == TILE_PLAYER2) return TILE_SEEN_PLAYER2;
            return pos;
        case RULE_CREATE:
            if (pl1 > pl2) return TILE_PLAYER1;
            else {
                if (pos == TILE_SEEN_PLAYER2 || pos == TILE_FREE)
                    return TILE_SEEN_PLAYER2;
                return TILE_PLAYER2;
            }
        case RULE_CREATE_STAY:
            if (pl1 > pl2) return TILE_PLAYER1;
            else {
                if (pos == TILE_SEEN_PLAYER2 || pos == TILE_FREE)
                    return TILE_SEEN_PLAYER2;
                return TILE_PLAYER2;
            }
    }

    abort("Error while processing game logic!");

    return 0; //:)
}
