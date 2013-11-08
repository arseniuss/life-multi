/* 
 * File:   Map.h
 * Author: arseniuss
 *
 * Created on piektdiena, 2013, 8 novembris, 10:38
 */

#pragma once

class Map {
private:
    void **data;
public:
    Map() {};
    ~Map() {};
    
    int NextGeneration();
};

