/* 
 * File:   Map.h
 * Author: arseniuss
 *
 * Created on piektdiena, 2013, 8 novembris, 10:38
 */

#pragma once

class Map {
private:
    void *data;
    int _width;
    int _height;
public:
    const int &width;
    const int &height;

    void create(int w, int h) {
        if(data) free(data);
        _width = w;
        _height = h;
        data = malloc(w * h * 4);
    };

    Map() : width(_width), height(_height) {
        _width = 0;
        _height = 0;
        data = NULL;
    };

    ~Map() {
    };

    int NextGeneration();
};

