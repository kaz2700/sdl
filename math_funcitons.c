#include "math_functions.h"
#include <stdio.h>
#include <math.h>


float distance(float pos1[], float pos2[]) {
    return sqrt( pow(pos2[0]-pos1[0], 2) + pow(pos2[1]-pos1[1], 2));
}