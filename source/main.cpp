/* 
 * File:   main.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 29 oktobris, 12:20
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "State.h"
#include "StateGame.h"
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

    //TODO: configuration allow or disallow resize
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    //TODO: detect display or use configuration
    if (!(display = al_create_display(500, 500)))
        abort("Could not create display!");

    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

    al_set_window_constraints(display, MIN_DISPLAY_WIDTH, MIN_DISPLAY_HEIGHT, 0, 0);

    if (!al_install_keyboard())
        abort("Could not install keyboard!");

    if (!al_install_mouse())
        abort("Could not install mouse!");

    if (!al_init_image_addon())
        abort("Could not init image addon!");

    if (!al_init_primitives_addon())
        abort("Could not init primitives addon!");

    if (!al_init_font_addon())
        abort("Could not init font addon!");

    if (!al_init_ttf_addon())
        abort("Could not init ttf addon!");

    if (!(xsmall_font = al_load_ttf_font(XSMALLFONT_TTF, 10, 0)))
        abort("Could not load font @ %s\n", XSMALLFONT_TTF);

    current_game = new StateGame;
    current_state = current_game;

    run();

    al_free(xsmall_font);
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_destroy_display(display);
    al_uninstall_system();

    return 0;
}

static void handle_event(ALLEGRO_EVENT &event) {
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
            current_state->user_display();
            app.need_redraw = true;
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
            //izslēgt/ieslēgt statistikas rādīšanu
            if (event.keyboard.keycode == ALLEGRO_KEY_F1) {
                if (app.stats) app.stats = false;
                else app.stats = true;
            }
            current_state->user_key(event.keyboard.keycode);
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            break;
        case ALLEGRO_EVENT_KEY_UP:
            break;
            /* Kad pakustina peli */
        case ALLEGRO_EVENT_MOUSE_AXES:
            current_state->user_mouse(event.mouse.x, event.mouse.y,
                    event.mouse.z, event.mouse.dx, event.mouse.dy,
                    event.mouse.dz);
            app.need_redraw = true;
            break;

            /* Kad nospiež peles pogu */
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            current_state->user_mouse_down(event.mouse.x, event.mouse.y,
                    event.mouse.z, event.mouse.dx, event.mouse.dy,
                    event.mouse.dz, event.mouse.button);
            break;

            /* Kad paceļ peles pogu */
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            current_state->user_mouse_up(event.mouse.x, event.mouse.y,
                    event.mouse.z, event.mouse.dx, event.mouse.dy,
                    event.mouse.dz, event.mouse.button);
            break;
        default:
            debug("Unknown event {type: %d}\n", event.type);
            break;
    }
}

static void run() {
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *fps_timer;
    ALLEGRO_TIMER *gps_timer;

    if (!(queue = al_create_event_queue()))
        abort("Count not create event queue!");

    if (!(fps_timer = al_create_timer(1.0 / FPS)))
        abort("Count not create timer!");

    if (!(gps_timer = al_create_timer(1.0 / GPS)))
        abort("Count not create timer!");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(fps_timer));
    al_register_event_source(queue, al_get_timer_event_source(gps_timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    al_start_timer(fps_timer);
    al_start_timer(gps_timer);

    while (app.loop) {
        while (!al_is_event_queue_empty(queue)) {
            ALLEGRO_EVENT event;

            al_wait_for_event(queue, &event);

            switch (event.type) {
                case ALLEGRO_EVENT_TIMER:
                    if (event.timer.source == fps_timer) {
                        app.need_redraw = true;
                    } else if (event.timer.source == gps_timer) {
                        app.need_update = true;
                    }
                    break;
                default:
                    handle_event(event);
                    break;
            }
        }

        if (app.need_redraw) {
            current_state->draw();
            if (app.stats) draw_stats();
            al_flip_display();
            app.need_redraw = false;
        }

        if (app.need_update) {
            current_state->update();
            app.need_update = false;
        }
    }

    al_stop_timer(fps_timer);
    al_stop_timer(gps_timer);
    al_destroy_timer(fps_timer);
    al_destroy_timer(gps_timer);
    al_destroy_event_queue(queue);
}
