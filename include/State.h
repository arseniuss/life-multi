/* 
 * File:   State.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 14:01
 */

/**
 * Šis fails apraksta spēles stāvokli. 
 * Paredzētie stāvokļi:
 * - Izvēle
 *      - Lokālās spēlēs uzstādīšana
 *      - Globālās spēlēs uzstādīšana
 *      - Rezultāti
 *      - Par autoriem
 * - Spēle
 */

#pragma once

#ifdef __cplusplus

#    include <allegro5/allegro.h>

#    include "debug.h"

/* Nezināms spēles stāvoklis */
#    define STATE_UNKNOWN                   0
/* Vienkarši izejams stāvoklis (nav jāsaglabā) */
#    define STATE_SIMPLE                    1
/* Notiek spēle */
#    define STATE_GAME                      2

class State {
private:

public:
    int type;

    State() : type(STATE_UNKNOWN) {
    };

    ~State() {
    };

    /* Pārzīmē stāvokli uz ekrāna */
    virtual void draw() {
    };

    /* Apstrādā lietotaja nospiesto tastatūras taustiņu */
    virtual void user_key(int key) {
    }; //TODO: modifiers?

    virtual void user_mouse(int x, int y, int z, int dx, int dy, int dz) {
    };

    virtual void user_display() {
    };

    virtual void user_mouse_down(int x, int y, int z, int dx, int dy, int dz,
            int button) {
    };

    virtual void user_mouse_up(int x, int y, int z, int dx, int dy, int dz,
            int button) {
    };

    virtual const char * stats() {
        return NULL;
    };
};

#endif
