#include "algorithm.h"

float linearMapping(int16_t in, int16_t in_min, int16_t in_max, float out_min, float out_max) {
    float result = float(out_min + (out_max - out_min) * (in - in_min) / (in_max - in_min));
    return result;
}

//
// Created by lychee on 2025/10/3.
//