/* 
 * File:   main.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 12:20
 */

#include <allegro5/allegro.h>
#include <cstdlib>
#include <iostream>

#include "config.h"
#include "debug.h"

using namespace std;

ALLEGRO_DISPLAY *display = NULL;

static void run();

int main(int argc, char** argv) {

    if (!al_init())
        abort("Could not init Allegro!");

    if (!al_install_keyboard())
        abort("Could not install keyboard!");

    if (!al_install_mouse())
        abort("Could not install mouse!");

    //TODO: detect display or use configuration
    if (!(display = al_create_display(500, 500)))
        abort("Could not create display!");

    run();

    return 0;
}

static void run() {
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    if (!(queue = al_create_event_queue()))
        abort("Count not create event queue!");

    if (!(timer = al_create_timer(1.0 / FPS)))
        abort("Count not create timer!");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    al_start_timer(timer);

    ALLEGRO_EVENT event;
    bool need_redraw = false;

    while (true) {
        if (need_redraw && al_event_queue_is_empty(queue)) {
            //draw();
            need_redraw = false;
        }

        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    return;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                need_redraw = true;
                break;
            default:
                debug("Unknown event {type: %d}\n", event.type);
                break;
        }
    }
    
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
