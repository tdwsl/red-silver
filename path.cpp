#include "path.hpp"
#include "map.hpp"
#include "unit.hpp"
#include "fov.hpp"

unsigned char g_pathMap[MAPSZ];

void generatePath(int x1, int y1) {
    for(int i = 0; i < g_mapw*g_maph; i++) {
        g_pathMap[i] = tileBlocks(g_map[i]) ? 255 : 0;
    }

    for(int i = 0; i < g_nunits; i++)
        if(g_fovMap[g_units[i]->y*g_mapw+g_units[i]->x])
            g_pathMap[g_units[i]->y*g_mapw+g_units[i]->x] = -1;

    g_pathMap[y1*g_mapw+x1] = 1;

    for(int g = 1; g < 128; g++) {
        for(unsigned long i = 0; i < g_mapw*g_maph; i++) {
            if(g_pathMap[i] != g) continue;
            for(int d = 0; d < 8; d++) {
                int x = g_dirs[d*2] + i % g_mapw;
                int y = g_dirs[d*2+1] + i / g_mapw;
                if(!inMapBounds(x, y)) continue;
                int t = g_pathMap[y*g_mapw+x];
                if(!t || (t != 255 && g+2+(d>=4) < t))
                    g_pathMap[y*g_mapw+x] = g+2+(d>=4);
            }
        }
    }

    /*for(unsigned long i = 0; i < g_mapw*g_maph; i++) {
        if(g_pathMap[i] == 255) printf("#");
        else if(g_pathMap[i] == 0) printf(".");
        else printf("%d", g_pathMap[i]%10);
        if((i+1)%g_mapw == 0) printf("\n");
    }*/
}

void backtrack(int &x, int &y) {
    int li = -1, ld = 255;
    int t1 = g_pathMap[y*g_mapw+x];
    for(int d = 0; d < 8; d++) {
        int xx = x + g_dirs[d*2];
        int yy = y + g_dirs[d*2+1];
        if(!inMapBounds(xx, yy)) continue;
        int t = g_pathMap[yy*g_mapw+xx];
        if(t && t < ld && t < t1) {
            li = d;
            ld = t;
        }
    }
    if(li != -1) {
        x += g_dirs[li*2];
        y += g_dirs[li*2+1];
    }
}

void backtrackh(int &x, int &y) {
    int hi = -1, hd = 0;
    int t1 = g_pathMap[y*g_mapw+x];
    for(int d = 0; d < 8; d++) {
        int xx = x + g_dirs[d*2];
        int yy = y + g_dirs[d*2+1];
        if(!inMapBounds(xx, yy)) continue;
        int t = g_pathMap[yy*g_mapw+xx];
        if(t && t < t1 && t > hd) {
            hi = d;
            hd = t;
        }
    }
    if(hi != -1) {
        x += g_dirs[hi*2];
        y += g_dirs[hi*2+1];
    }
}

bool pathBlocked(int t, int ap) {
    return (t == 0 || t > ap || t == 255);
}

