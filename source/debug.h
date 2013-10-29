/* 
 * File:   debug.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 13:11
 */

#pragma once

#ifdef __cplusplus
#    include <cstdio>

using namespace std;

#else
#    include <stdio.h>
#endif

/** Labošanas paziņojumi, kas parādās tikai DEBUG versijā */
#ifdef DEBUG
#    define debug(fmt, ...)                                                    \
                        do {                                                   \
                                printf("%s:%d: ", __FILE__, __LINE__);         \
                                printf(fmt, ##__VA_ARGS__);                    \
                        } while(0);
#else
#    define debug(fmt, ...)
#endif

#define abort(fmt, ...)                                                        \
                do {                                                           \
                        fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);        \
                        fprintf(stderr, fmt, ##__VA_ARGS__);                   \
                } while(0);
