#ifndef particle_header
#define particle_header

struct {
    float position[2];
    float velocity[2];
    float radius;
    float mass;
} typedef Particle;

void drawParticle(Particle* particle);

#endif // ADDITIONAL_H