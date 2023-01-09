#include "fov.hpp"
#include "map.hpp"
#include "unit.hpp"
#include <stdio.h>

bool g_fovMap[MAPSZ];

void getFov(int t) {
    for(unsigned long i = 0; i < g_mapw*g_maph; i++)
        g_fovMap[i] = false;

    for(int i = 0; i < g_nunits; i++) {
        if(g_units[i]->team != t) continue;
        g_fovMap[g_units[i]->y*g_mapw+g_units[i]->x] = true;
        for(int xy = 0; xy < UNIT_VIEWDIST2*UNIT_VIEWDIST2; xy++) {
            int x = g_units[i]->x - UNIT_VIEWDIST + xy%UNIT_VIEWDIST2;
            int y = g_units[i]->y - UNIT_VIEWDIST + xy/UNIT_VIEWDIST2;
            if(g_units[i]->sees(x, y))
                g_fovMap[y*g_mapw+x] = true;
        }
    }
}

