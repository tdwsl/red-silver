#include "images.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <assert.h>

ALLEGRO_BITMAP *b_squad;
ALLEGRO_BITMAP *b_map;
ALLEGRO_BITMAP *b_font;
ALLEGRO_BITMAP *b_ui;

void loadImages() {
    b_squad = al_load_bitmap("img/squad.png");
    assert(b_squad);
    b_map = al_load_bitmap("img/map.png");
    assert(b_map);
    b_font = al_load_bitmap("img/font.png");
    assert(b_font);
    b_ui = al_load_bitmap("img/ui.png");
    assert(b_ui);
}

void freeImages() {
    al_destroy_bitmap(b_ui);
    al_destroy_bitmap(b_font);
    al_destroy_bitmap(b_map);
    al_destroy_bitmap(b_squad);
}

