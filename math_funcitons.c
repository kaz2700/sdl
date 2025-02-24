#include "math_functions.h"
#include <stdio.h>
#include <math.h>


float distance_on_motion(float pos1[], float pos2[], float vel1[], float vel2[], float dt) {
    return sqrt( pow(dt * (vel2[0] - vel1[0]) + pos2[0]-pos1[0], 2) + pow(dt * (vel2[1] - vel1[1]) + pos2[1]-pos1[1], 2));
}

float distance(float pos1[], float pos2[]) {
    return sqrt( pow(pos2[0]-pos1[0], 2) + pow(pos2[1]-pos1[1], 2));
}