#include "unit.hpp"
#include "images.hpp"
#include "draw.hpp"
#include "map.hpp"
#include "path.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

Unit *g_units[200];
int g_nunits = 0;

Unit::Unit(int x, int y, int team) {
    Unit::x = x;
    Unit::y = y;
    Unit::team = team;
    index = g_nunits++;
    g_units[index] = this;
}

Unit::~Unit() {
    g_units[index] = g_units[--g_nunits];
}

void Unit::draw(int xo, int yo, bool dn) {
    drawBitmap(b_squad, equipped*16, team*32+dn*16, 16, 16,
               x*16+Unit::xo+xo, y*16+Unit::yo+yo);
}

void Unit::update() {
    switch(mode) {
    case MODE_WALKING:
        if(xo < 0) xo--;
        else if(xo > 0) xo++;
        if(yo < 0) yo--;
        else if(yo > 0) yo++;

        if(xo >= 16 || yo >= 16 || xo <= -16 || yo <= -16) {
            x += xo/16;
            y += yo/16;
            if(g_pathMap[y*g_mapw+x] == 1)
                mode = MODE_NORMAL;
            else {
                int xx = x, yy = y;
                backtrack(xx, yy);
                xo = xx-x;
                yo = yy-y;
            }
        }
        break;
    }
}

Unit *unitAt(int x, int y) {
    for(int i = 0; i < g_nunits; i++)
        if(g_units[i]->x == x && g_units[i]->y == y) return g_units[i];
    return 0;
}

