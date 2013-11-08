/* 
 * File:   draw_text.h
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 17:01
 */

/**
 * Teksta zīmēšanas funkcijas
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdio>
#include <cstring>

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int x, int y,
        const char *text) {
    char *atext = (char *)malloc(strlen(text)+1);
    strcpy(atext, text);
    char *pch = strtok(atext, "\n");
    int starty = y;
     
    while(pch != NULL) {
        al_draw_text(font, color, x, starty, 0, pch);
        //pāriet jaunā rindiņā
        starty += al_get_font_line_height(font);
        pch = strtok(NULL,"\n");
    }    
}
