#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

extern int g_scale;

void drawBitmap(ALLEGRO_BITMAP *b, int cx, int cy, int cw, int ch,
                int dx, int dy);
void drawTintedBitmap(ALLEGRO_BITMAP *b, ALLEGRO_COLOR col,
                      int cx, int cy, int cw, int ch,
                      int dx, int dy);
void drawText(const char *s, int x, int y);
void drawMap(int xo, int yo);
void drawPath(int xo, int yo, int ap, int ap2);

