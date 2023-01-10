#include "unit.hpp"
#include "images.hpp"
#include "draw.hpp"
#include "map.hpp"
#include "path.hpp"
#include "unit.hpp"
#include "util.hpp"
#include "fov.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

Unit *g_units[200];
int g_nunits = 0;

extern int g_playerTeam;

Unit::Unit(int x, int y, int team) {
    Unit::x = x;
    Unit::y = y;
    Unit::team = team;
    index = g_nunits++;
    g_units[index] = this;
    if(team == g_playerTeam) getFov(team);
}

Unit::~Unit() {
    g_units[index] = g_units[--g_nunits];
    if(team == g_playerTeam) getFov(team);
}

void Unit::draw(int xo, int yo, bool dn) {
    if(!g_fovMap[y*g_mapw+x]) return;
    drawBitmap(b_squad, equipped*16, team*32+dn*16, 16, 16,
               x*16+Unit::xo+xo, y*16+Unit::yo+yo);
}

void Unit::update() {
    switch(mode) {
    case MODE_WALKING:
        if(counter) { counter--; break; }

        if(xo < 0) xo -= UNIT_SPEED;
        else if(xo > 0) xo += UNIT_SPEED;
        if(yo < 0) yo -= UNIT_SPEED;
        else if(yo > 0) yo += UNIT_SPEED;

        if(xo >= 16 || yo >= 16 || xo <= -16 || yo <= -16) {
            x += xo/16;
            y += yo/16;
            xo = 0;
            yo = 0;
            counter = 2;
            if(team == g_playerTeam)
                getFov(g_playerTeam);
            generatePath(tx, ty);
        }

        if(xo == 0 && yo == 0) {
            if(g_pathMap[y*g_mapw+x] == 1)
                mode = MODE_NORMAL;
            else {
                int xx = x, yy = y;
                backtrack(xx, yy);
                xo = xx-x;
                yo = yy-y;
                if(xo && yo) ap -= 3;
                else ap -= 2;
            }
        }
        break;
    }
}

void Unit::walk(int tx, int ty) {
    if(mode != MODE_NORMAL) return;
    counter = 0;
    xo = 0;
    yo = 0;
    mode = MODE_WALKING;
    Unit::tx = tx;
    Unit::ty = ty;
}

bool Unit::sees(int x, int y) {
    int xd = x-Unit::x, yd = y-Unit::y;

    if(xd*xd+yd*yd > UNIT_VIEWDIST*UNIT_VIEWDIST) return false;
    if(!inMapBounds(x, y)) return false;

    int d = max(pos(xd), pos(yd));

    for(int i = 1; i <= d; i++) {
        int xx = Unit::x + (i*xd)/d;
        int yy = Unit::y + (i*yd)/d;
        if(xx == x && yy == y) return true;
        if(tileBlocksVision(g_map[yy*g_mapw+xx])) return false;
    }

    return false;
}

Unit *unitAt(int x, int y) {
    for(int i = 0; i < g_nunits; i++)
        if(g_units[i]->x == x && g_units[i]->y == y) return g_units[i];
    return 0;
}

