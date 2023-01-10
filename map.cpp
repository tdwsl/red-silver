#include "map.hpp"

unsigned char g_map[3999];
unsigned int g_mapw, g_maph;

const char g_dirs[] = {
  0, -1,
  1, 0,
  0, 1,
  -1, 0,
  1, -1,
  1, 1,
  -1, 1,
  -1, -1,
};

bool inMapBounds(int x, int y) {
    return (x >= 0 && y >= 0 && x < g_mapw && y < g_maph);
}

bool tileBlocks(int t) {
    switch(t) {
    case 1: case 2: case 4: case 5:
        return true;
    default:
        return false;
    }
}

bool tileBlocksVision(int t) {
    switch(t) {
    case 1: case 2:
        return true;
    default:
        return false;
    }
}

void loadMapArr(unsigned char *m) {
    g_mapw = *(m++);
    g_maph = *(m++);
    for(int i = 0; i < g_mapw*g_maph; i++) g_map[i] = m[i];
}

