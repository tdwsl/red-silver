#include "draw.hpp"
#include "map.hpp"
#include "images.hpp"
#include "path.hpp"
#include "alinit.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int g_scale = 3;

void drawBitmap(ALLEGRO_BITMAP *b, int cx, int cy, int cw, int ch,
                int dx, int dy)
{
    if(dx < 0) { cw += dx; cx -= dx; dx = 0; }
    if(dy < 0) { ch += dy; cy -= dy; dy = 0; }
    if(cw < 0 || ch < 0) return;
    al_draw_scaled_bitmap(b, cx, cy, cw, ch,
                          dx*g_scale, dy*g_scale,
                          cw*g_scale, ch*g_scale, 0);
}

void drawTintedBitmap(ALLEGRO_BITMAP *b, ALLEGRO_COLOR col,
                      int cx, int cy, int cw, int ch, int dx, int dy)
{
    if(dx < 0) { cw += dx; cx -= dx; dx = 0; }
    if(dy < 0) { ch += dy; cy -= dy; dy = 0; }
    if(cw < 0 || ch < 0) return;
    al_draw_tinted_scaled_bitmap(b, col, cx, cy, cw, ch,
                                 dx*g_scale, dy*g_scale,
                                 cw*g_scale, ch*g_scale, 0);
}

void drawText(const char *s, int x, int y) {
    int xx = x;
    for(const char *c = s; *c; c++) {
        drawBitmap(b_font, ((*c)%32)*8, ((*c)/32)*8, 8, 8, xx, y);
        xx += 8;
        if(*s == '\n') { xx = x; y++; }
    }
}

void drawTintedText(const char *s, ALLEGRO_COLOR col, int x, int y) {
    int xx = x;
    for(const char *c = s; *c; c++) {
        drawTintedBitmap(b_font, col, ((*c)%32)*8, ((*c)/32)*8, 8, 8, xx, y);
        xx += 8;
        if(*s == '\n') { xx = x; y++; }
    }
}

bool joinsWall(int t) {
    return (t >= 1 && t <= 5);
}

int doorTile(int i) {
    int t = 0;
    int x = i % g_mapw;
    int y = i / g_mapw;
    if(inMapBounds(x, y-1) && joinsWall(g_map[(y-1)*g_mapw+x])) t = 1;
    else if(inMapBounds(x, y+1) && joinsWall(g_map[(y+1)*g_mapw+x])) t = 1;
    return t;
}

void drawMap(int xo, int yo) {
    for(unsigned long i = 0; i < g_mapw*g_maph; i++) {
        int t;
        switch(g_map[i]) {
        case 1:
            t = 0;
            for(int d = 0; d < 4; d++) {
                int x = g_dirs[d*2] + i % g_mapw;
                int y = g_dirs[d*2+1] + i / g_mapw;
                if(!inMapBounds(x, y)) continue;
                int j = y*g_mapw+x;
                if(joinsWall(g_map[y*g_mapw+x])) t |= 1 << d;
            }
            t += 16;
            break;
        case 2: t = 2 + doorTile(i); break;
        case 3: t = 4 + doorTile(i); break;
        case 4: t = 6 + doorTile(i); break;
        case 5: t = 8 + doorTile(i); break;
        case 6: t = 10 + doorTile(i); break;
        default:
            t = g_map[i];
            break;
        }
        drawBitmap(b_map, (t%8)*16, (t/8)*16, 16, 16,
                   (i % g_mapw)*16+xo, (i / g_mapw)*16+yo);
    }
}

void drawPath(int xo, int yo, int ap, int ap2) {
    for(unsigned long i = 0; i < g_mapw*g_maph; i++) {
        if(g_pathMap[i] == 255 || g_pathMap[i] <= 1) continue;
        ALLEGRO_COLOR col = al_map_rgba(128, 255, 128, 128);
        if(g_pathMap[i] > ap+1) col = al_map_rgba(255, 200, 128, 128);
        if(g_pathMap[i] > ap2+1) col = al_map_rgba(255, 128, 128, 128);;
        drawTintedBitmap(b_ui, col, 32, 0, 16, 16,
                         (i%g_mapw)*16+xo, (i/g_mapw)*16+yo);
    }
}

