/* 
 * File:   StateMenu.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 14:43
 */

#pragma once

#ifdef __cplusplus

#    include "State.h"

class StateMenu : public State {
public:
    typedef State super;
    
    StateMenu();
    void draw();
    void user_key(int key);
};

#endif