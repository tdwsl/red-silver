#include "alinit.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <assert.h>

ALLEGRO_DISPLAY *g_disp;
ALLEGRO_TIMER *g_timer;
ALLEGRO_EVENT_QUEUE *g_queue;

void initAl() {
    assert(al_init());
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    assert(al_install_mouse());

    g_timer = al_create_timer(1.0 / 30.0);
    assert(g_timer);
    g_queue = al_create_event_queue();
    assert(g_queue);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    g_disp = al_create_display(640, 480);
    assert(g_disp);
    al_hide_mouse_cursor(g_disp);

    al_register_event_source(g_queue, al_get_keyboard_event_source());
    al_register_event_source(g_queue, al_get_display_event_source(g_disp));
    al_register_event_source(g_queue, al_get_timer_event_source(g_timer));

    al_start_timer(g_timer);
}

void endAl() {
    al_destroy_display(g_disp);
    al_destroy_event_queue(g_queue);
    al_destroy_timer(g_timer);
}

