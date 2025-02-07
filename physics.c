#include "physics.h"
#include "particle.h"
#include "artist.h"
#include <stdio.h>
#include "math_functions.h"

void update_positions(Particle* particle, float* dt) {
    particle -> velocity[1] = particle -> velocity[1] - 9.81 * *dt;

    particle -> position[0] = particle -> position[0] + particle -> velocity[0] * *dt;
    particle -> position[1] = particle -> position[1] + particle -> velocity[1] * *dt;
}

void check_limits(Particle* particle) { 
    if (particle -> position[1] > box_length || particle -> position[1] < particle -> radius) {
        particle -> position[1] = particle -> radius;
        particle -> velocity[1] = -0.95 * particle -> velocity[1];
    }

    if (particle -> position[0] > box_length || particle -> position[0] < particle -> radius) {
        //particle -> position[0] = particle -> radius;
        particle -> velocity[0] = -0.95 * particle -> velocity[0];
    }
}

void check_collisions(int particle_index, Particle particles[], int num_of_particles) {
    for(int i = 0; i < num_of_particles; i++) {
        if (particle_index == i)
            continue;
        
        if(distance(particles[particle_index].position, particles[i].position) < particles[i].radius) {
                particles[particle_index].velocity[0] = -particles[particle_index].velocity[0];
                particles[particle_index].velocity[1] = -particles[particle_index].velocity[1];
                particles[i].velocity[0] = -particles[i].velocity[0];
                particles[i].velocity[1] = -particles[i].velocity[1];
            }
        } 
}
void tick(Particle particles[], float* dt, int num_of_particles) {
    for(int i = 0; i < num_of_particles; i++) {
            update_positions(&particles[i], dt);
            check_collisions(i, particles, num_of_particles);
            check_limits(&particles[i]);
        } 
}