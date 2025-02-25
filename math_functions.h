#include "particle.h"

#ifndef math_functions_header
#define math_functions_header

float distance_on_motion(Particle* particle1, Particle* particle2, float dt);
float radial_velocity(Particle* particle1, Particle* particle2);
float distance(float pos1[], float pos2[]);

#endif