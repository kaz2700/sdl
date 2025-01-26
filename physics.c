#include "physics.h"
#include "particle.h"
#include <stdio.h>

void gravity(Particle* particle, float* dt) {
    particle -> velocity[1] = particle -> velocity[1] - 9.81 * *dt;

    particle -> position[0] = particle -> position[0] + particle -> velocity[0] * *dt;
    particle -> position[1] = particle -> position[1] + particle -> velocity[1] * *dt;
}