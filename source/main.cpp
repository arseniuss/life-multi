/* 
 * File:   main.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 12:20
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdlib>
#include <iostream>

#include "State.h"
#include "StateMenu.h"
#include "config.h"
#include "debug.h"
#include "global.h"

using namespace std;

ALLEGRO_DISPLAY *display = NULL;
State *current_state = NULL;

App app;
static void run();

int main(int argc, char** argv) {

    if (!al_init())
        abort("Could not init Allegro!");

    al_set_app_name(APP_NAME);

    uint32_t version = al_get_allegro_version();
    int major = version >> 24;
    int minor = (version >> 16) & 255;
    int revision = (version >> 8) & 255;
    int release = version & 255;

    log("found Allegro %d.%d.%d[%d]\n", major, minor, revision, release);

    //TODO: check if is usable Allegro version

    if (!al_install_keyboard())
        abort("Could not install keyboard!");

    if (!al_install_mouse())
        abort("Could not install mouse!");

    if (!al_init_image_addon())
        abort("Could not init image addon!");

    al_init_font_addon();

    if (!al_init_ttf_addon())
        abort("Could not inir ttf addon!");
    
    //TODO: configuration allow or disallow resize
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    //TODO: detect display or use configuration
    if (!(display = al_create_display(500, 500)))
        abort("Could not create display!");

    if (!(xsmall_font = al_load_ttf_font(XSMALLFONT_TTF, 10, 0)))
        abort("Could not load font @ %s\n", XSMALLFONT_TTF);

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
    current_state = new StateMenu;

    while (app.loop) {
        if (need_redraw && al_event_queue_is_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_stats();
            current_state->draw();
            al_flip_display();
            need_redraw = false;
        }

        al_wait_for_event(queue, &event);

        switch (event.type) {
            
            /* Kad pele iziet no loga */
            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
                break;
            
            /* Kad pele atgriežas logā*/
            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                break;

                /* Kad maina loga izmēru*/
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(event.display.source);
                break;

                /* Kad aizver logu */
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (current_state->type == STATE_GAME) {
                    //goto StateSave(current_state)
                } else {
                    return;
                }
                break;

                /* Kad nospiež kādu klaviatūras taustiņu*/
            case ALLEGRO_EVENT_KEY_CHAR:
                current_state->user_key(event.keyboard.keycode);
                break;

                /* Taimeris */
            case ALLEGRO_EVENT_TIMER:
                need_redraw = true;
                break;

                /* Kad pakustina peli */
            case ALLEGRO_EVENT_MOUSE_AXES:
                current_state->user_mouse(event.mouse.x, event.mouse.y, 0);
                break;

                /* Kad nospiež peles pogu */
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                current_state->user_mouse(event.mouse.x, event.mouse.y,
                        event.mouse.button);
                break;

                /* Kad paceļ peles pogu */
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                current_state->user_mouse(event.mouse.x, event.mouse.y,
                        event.mouse.button);
                break;
            default:
                debug("Unknown event {type: %d}\n", event.type);
                break;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
