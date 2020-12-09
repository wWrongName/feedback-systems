#include "validation.hpp"
#include <cmath>

#define NUM_BEGIN 48

float validate_number(string number) {
    float ret_val = 0;
    uint multiplier = 0;
    for (auto it = number.begin(); it != number.end(); it++) {
        if (multiplier != 0)
            multiplier++;
        if (*it >= NUM_BEGIN && *it < (NUM_BEGIN + 10)) {
            ret_val = (float)(*it - NUM_BEGIN) + ret_val * 10;
        }
        else if (*it == '.') {
            multiplier = 1;
        }
        else {
            return -1;
        }
    }
    if (multiplier == 0) {
        return ret_val;
    }
    else if (multiplier == 1) {
        return -1;
    }
    else
        return ret_val / pow(10, --multiplier);
};

bool is_valid_fraction(float var) {
    if (var >= 0 && var <= 1) 
        return true;
    return false;
};