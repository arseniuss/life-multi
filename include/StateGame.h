/* 
 * File:   StateGame.h
 * Author: arseniuss
 *
 * Created on trešdiena, 2013, 30 oktobris, 15:54
 */

#pragma once

#include "State.h"

class StateGame : public State {
public:
    StateGame();
    ~StateGame();
    void draw();
    void user_key(int key);
};
