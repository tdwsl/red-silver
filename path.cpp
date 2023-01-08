#include "path.hpp"
#include "map.hpp"

unsigned char g_pathMap[MAPSZ];

void generatePath(int x1, int y1) {
    for(int i = 0; i < g_mapw*g_maph; i++) {
        g_pathMap[i] = tileBlocks(g_map[i]) ? 255 : 0;
    }

    g_pathMap[y1*g_mapw+x1] = 1;

    for(int g = 1; g < 255; g++) {
        for(int i = 0; i < g_mapw*g_maph; i++) {
            if(g_pathMap[i] != g) continue;
            for(int d = 0; d < 8; d++) {
              int x = g_dirs8[d*2] + i % g_mapw;
              int y = g_dirs8[d*2+1] + i / g_mapw;
              if(!inMapBounds(x, y)) continue;
              if(g_pathMap[y*g_mapw+x] == 0)
                  g_pathMap[y*g_mapw+x] = g+1;
            }
        }
    }
}

void backtrack(int &x, int &y) {
    for(int d = 0; d < 8; d++) {
        int xx = x + g_dirs8[d*2];
        int yy = y + g_dirs8[d*2+1];
        if(!inMapBounds(xx, yy)) continue;
        if(g_pathMap[yy*g_mapw+xx] == g_pathMap[y*g_mapw+x]-1) {
            x = xx;
            y = yy;
            return;
        }
    }
}
