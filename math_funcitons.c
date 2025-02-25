#include "math_functions.h"
#include <stdio.h>
#include <math.h>
#include "particle.h"
#include "string.h"


float distance_on_motion(Particle* particle1, Particle* particle2, float dt) {
    float* pos1 = particle1 -> position;
    float* pos2 = particle2 -> position;
    float* vel1 = particle1 -> velocity;
    float* vel2 = particle2 -> velocity;

    return sqrt( pow(dt * (vel2[0] - vel1[0]) + pos2[0]-pos1[0], 2) + pow(dt * (vel2[1] - vel1[1]) + pos2[1]-pos1[1], 2));
}

float radial_velocity(Particle* particle1, Particle* particle2){
    float* pos1 = particle1 -> position;
    float* pos2 = particle2 -> position;
    float* vel1 = particle1 -> velocity;
    float* vel2 = particle2 -> velocity;

    return 1 / distance(particle1 -> position, particle2 -> position) * ((pos2[0] - pos1[0]) * (vel2[0] - vel1[0]) + (pos2[1] - pos1[1]) * (vel2[1] - vel1[1]));
}

float distance(float pos1[], float pos2[]) {
    return sqrt( pow(pos2[0]-pos1[0], 2) + pow(pos2[1]-pos1[1], 2));
}