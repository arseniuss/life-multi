/* 
 * File:   config.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 13:42
 */

#pragma once

#define PLATFORM_WINDOWS                1
#define PLATFORM_MAC                    2
#define PLATFORM_UNIX                   3

//nosaka operētājsistēmu
#if defined(_WIN32)
#    define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#    define PLATFORM PLATFORM_MAC
#elif defined(__unix)
#    define PLATFORM PLATFORM_UNIX
#else
#    error "Unknown environment!"
#endif

#define FPS                             32
#define GPS                             8

#define APP_NAME                        "Life Game Multiplayer"
#define APP_VERSION                     0x100

#define XSMALLFONT_TTF                  "resources/DejaVuSans.ttf"
#define PIXELETTE_TTF                   "resources/pixelated.ttf"

#define MIN_DISPLAY_WIDTH               500
#define MIN_DISPLAY_HEIGHT              500
#define MIN_TILE_SIZE                   8
