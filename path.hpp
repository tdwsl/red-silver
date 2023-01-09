#pragma once

extern unsigned char g_pathMap[];

void generatePath(int x1, int y1);
void backtrack(int &x, int &y);
void backtrackh(int &x, int &y);
bool pathBlocked(int t, int ap);

