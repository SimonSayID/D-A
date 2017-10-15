//
// Created by simon on 8/27/17.
//

#include "main.h"

#ifndef max
int max(int a, int b){
    if (a > b) {
        return a;
    }
    return b;
}
#endif

static int is_prime(size_t num) {
    for (int i = 3;; i += 2) {
        size_t q = num / i;
        if (q < i) {
            return 1;
        }
        if (num == q * i) {
            return 0;
        }
    }
}

size_t next_prime(size_t num) {
    if (num < 2) {
        return 2;
    }
    if (!(num & 1)) {
        num += 1;
    } else {
        num += 2;
    }
    for (; !is_prime(num); num += 2) {

    }
    return num;
}