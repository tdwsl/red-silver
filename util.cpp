#include "util.hpp"

void clamp(int &n, int min, int max) {
    if(n < min) n = min;
    else if(n > max) n = max;
}

