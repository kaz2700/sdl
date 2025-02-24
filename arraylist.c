#include <stddef.h>
#include <stdio.h>
#include "particle.h"
#include "artist.h"

void init_arraylist(void** particles, int num_of_particles) {
    for(int i = 0; i < num_of_particles; i++) {
        particles[i] = malloc(sizeof(Particle));
        if (!particles[i]) {
            perror("Memory allocation failed");
            exit(1);
        }
    }

    Particle original_particle;

    original_particle.position[0] = box_length / 2;
    original_particle.position[1] = box_length / 2;
    original_particle.velocity[0] = 0;
    original_particle.velocity[1] = 0;
    original_particle.radius = 0.01;
    original_particle.mass = 1;
    original_particle.charge = 0.05;
    original_particle.id = 0;

    for(int i = 0; i < num_of_particles; i++) {
            Particle* particle = (Particle*) particles[i];
            *particle = original_particle;
            if (i != 0) {
                particle -> position[0] = (float) random() / RAND_MAX * box_length;
                particle -> position[1] = (float) random() / RAND_MAX * box_length;
                particle -> velocity[0] = (float) random() / RAND_MAX;
                particle -> velocity[1] = (float) random() / RAND_MAX;
                particle -> id = i;
            }
        }
}