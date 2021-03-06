/* 
 * File:   Map.h
 * Author: arseniuss
 *
 * Created on piektdiena, 2013, 8 novembris, 10:38
 */

#pragma once

#include <cstddef>
#include <cstdlib>

#include "global.h"

class Map {
private:
    unsigned char *data;
    unsigned char *buf;

    unsigned int _size;

    int _width;
    int _height;
    int _generation;
    int _population1;
    int _population2;
public:
    const int &width;
    const int &height;
    const int &generation;
    const int &population1;
    const int &population2;
    const unsigned int &size;

    void create(int w, int h) {
        if (data) free(data);
        _width = w;
        _height = h;
        _size = w * h;
        _generation = 0;
        data = (unsigned char *) malloc(_size);
        buf = (unsigned char *) malloc(_size);
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
                set(i, j, TILE_UNKNOWN);
    };

    Map() : width(_width), height(_height), generation(_generation),
    population1(_population1), population2(_population2), size(_size) {
        _width = 0;
        _height = 0;
        data = NULL;
        _generation = 0;
        _size = 0;
    };

    ~Map() {
    };

    int pos(int x, int y) const;
    void set(int x, int y, int v) const;

    int NextGeneration();
    void save(void *&buffer, int &sz) const;
    void load(void * buffer, int sz, int w, int h, int g);
};



