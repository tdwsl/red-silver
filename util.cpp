#include "util.hpp"

void clamp(int &n, int min, int max) {
    if(n < min) n = min;
    else if(n > max) n = max;
}

int pos(int n) {
    if(n < 0) n *= -1;
    return n;
}

int max(int n, int m) {
    return (n > m) ? n : m;
}

