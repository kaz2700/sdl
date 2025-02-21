#include "physics.h"
#include "particle.h"
#include "artist.h"
#include <stdio.h>
#include "math_functions.h"
#include <math.h>

float collision_energy_transmission = 0.75;
float gravity = 10;
float k = 1;

void update_positions(Particle* particle, float dt) {

    particle -> velocity[0] = particle -> velocity[0] + particle -> acceleration[0] * dt;
    particle -> velocity[1] = particle -> velocity[1] + particle -> acceleration[1] * dt;

    check_limits(particle, dt);

    particle -> position[0] = particle -> position[0] + particle -> velocity[0] * dt;
    particle -> position[1] = particle -> position[1] + particle -> velocity[1] * dt;
}

void check_limits(Particle* particle, float dt) {
    if (particle -> position[1] + particle -> radius + particle -> velocity[1] * dt > box_length ||
        particle -> position[1] - particle -> radius + particle -> velocity[1] * dt  < 0)
            particle -> velocity[1] = -1 * collision_energy_transmission * particle -> velocity[1];

    if (particle -> position[0] + particle -> radius + particle -> velocity[0] * dt  > box_length ||
        particle -> position[0] - particle -> radius + particle -> velocity[0] * dt  < 0)
            particle -> velocity[0] = -1 * collision_energy_transmission * particle -> velocity[0];
}

void check_collision(Particle* particle1, Particle* particle2) {
    if(distance(particle1 -> position, particle2 -> position) <= particle1 -> radius + particle2 -> radius)
        collision(particle1, particle2);
}

void collision(Particle* particle1, Particle* particle2) {
    float x11 = particle1 -> position[0];
    float x12 = particle1 -> position[1];
    float x21 = particle2 -> position[0];
    float x22 = particle2 -> position[1];
    float v11 = particle1 -> velocity[0];
    float v12 = particle1 -> velocity[1];
    float v21 = particle2 -> velocity[0];
    float v22 = particle2 -> velocity[1];
    float m1 = particle1 -> mass;
    float m2 = particle2 -> mass;

    particle1 -> velocity[0] = collision_energy_transmission * (v11 - 2*m2/(m1+m2) * (v11 - v21) * (x11 - x21) / (x11 - x21)); 
    particle1 -> velocity[1] = collision_energy_transmission * (v12 - 2*m2/(m1+m2) * (v12 - v22) * (x12 - x22) / (x12 - x22));
    particle2 -> velocity[0] = collision_energy_transmission * (v21 - 2*m1/(m1+m2) * (v21 - v11) * (x21 - x11) / (x21 - x11));
    particle2 -> velocity[1] = collision_energy_transmission * (v22 - 2*m1/(m1+m2) * (v22 - v12) * (x22 - x12) / (x22 - x12));
}

float* repulsion_force(Particle* particle1, Particle* particle2) {
    static float repulsion_force[2];

    float q1 = particle1 -> charge;
    float q2 = particle2 -> charge;

    float d = distance(particle1 -> position, particle2 -> position);
    
    float repulsion_force_norm = k * q1 * q2 / pow(d, 2);


    float cos = (particle1 -> position[0] - particle2 -> position[0])/d;
    float sin = (particle1 -> position[1] - particle2 -> position[1])/d;

    repulsion_force[0] = repulsion_force_norm * cos;
    repulsion_force[1] = repulsion_force_norm * sin;

    return repulsion_force;
    //change acceleration, add acceleration
}

void update_acceleration(Particle particles[], int particle_index, int num_of_particles) {
    particles[particle_index].acceleration[0] = 0;
    particles[particle_index].acceleration[1] = -gravity;

    for(int i = 0; i < num_of_particles; i++) {
        if (particle_index == i)
            continue;    
        //todo not call twice
        //particles[particle_index].acceleration[0] = particles[particle_index].acceleration[0] + repulsion_force(&particles[particle_index], &particles[i])[0]/particles[particle_index].mass;
        //particles[particle_index].acceleration[1] = particles[particle_index].acceleration[1] + repulsion_force(&particles[particle_index], &particles[i])[1]/particles[particle_index].mass;
        
        check_collision(&particles[particle_index], &particles[i]);
    } 
}
    //todo add viscosity

void tick(Particle particles[], float dt, int num_of_particles) {
    for(int i = 0; i < num_of_particles; i++) {
            
            update_acceleration(particles, i, num_of_particles);
            update_positions(&particles[i], dt);
        } 
}