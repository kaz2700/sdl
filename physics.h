#include "particle.h"

#ifndef physics_header
#define physics_header

//float gravity_value = 9.81;

extern float collision_energy_transmission;
extern float gravity;
extern float k;

void update_positions(Particle* particle, float* dt);
void check_limits(Particle* particle);
void check_collision(Particle* particle1, Particle* particle2);
void collision(Particle* particle1, Particle* particle2);
void particle_interactions_with_particles(Particle particles[], int particle_index, int num_of_particles);
void repulsion(Particle* particle1, Particle* particle2);
void update_acceleration(Particle* particle);
void tick(Particle* particles, float* dt, int num_of_particles);

#endif