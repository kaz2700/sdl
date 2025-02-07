#include "particle.h"

#ifndef physics_header
#define physics_header

//float gravity_value = 9.81;

void update_positions(Particle* particle, float* dt);
void check_limits(Particle* particle);
void check_collisions(int particle_index, Particle particles[], int num_of_particles);
void tick(Particle* particles, float* dt, int num_of_particles);

#endif