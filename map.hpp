#pragma once

#define MAPSZ 3999

extern unsigned char g_map[];
extern const char g_dirs8[];
extern const char g_dirs4[];
extern unsigned int g_mapw, g_maph;

bool inMapBounds(int x, int y);
bool tileBlocks(int t);
void loadMapArr(unsigned char *m);

