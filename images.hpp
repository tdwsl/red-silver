#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

extern ALLEGRO_BITMAP *b_squad;
extern ALLEGRO_BITMAP *b_map;
extern ALLEGRO_BITMAP *b_font;
extern ALLEGRO_BITMAP *b_ui;

void loadImages();
void freeImages();

