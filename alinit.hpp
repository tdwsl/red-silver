#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

extern ALLEGRO_DISPLAY *g_disp;
extern ALLEGRO_TIMER *g_timer;
extern ALLEGRO_EVENT_QUEUE *g_queue;

void initAl();
void endAl();

