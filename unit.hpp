#pragma once

class Unit {
    char xo = 0, yo = 0;
    int counter;
    int equipped = 0;
    int index;

public:
    enum {
        MODE_NORMAL,
        MODE_WALKING,
    };

    enum {
        TEAM_RED = 0,
        TEAM_PURPLE = 1,
    };

    char mode = MODE_NORMAL;
    int team;
    int hp = 25, maxHP = 25;
    int ap = 25, maxAP = 25;
    int x, y;

    Unit(int x, int y, int team);
    ~Unit();
    void draw(int xo, int yo, bool dn);
    void update();
};

extern Unit *g_units[200];
extern int g_nunits;

Unit *unitAt(int x, int y);

