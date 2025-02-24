#include <SDL2/SDL.h>
#include <stdio.h>
#include "physics.h"
#include "particle.h"
#include <unistd.h>
#include "artist.h"
#include <time.h>
#include "arraylist.h"

float dt = 0.01; //seconds

void initialize_particle(Particle* particles, int num_of_particles) {
    Particle particle;

    particle.position[0] = box_length / 2;
    particle.position[1] = box_length / 2;
    particle.velocity[0] = 0;
    particle.velocity[1] = 0;
    particle.radius = 0.01;
    particle.mass = 1;
    particle.charge = 0.05;
    particle.id = 0;

    for(int i = 0; i < num_of_particles; i++) {
            particles[i] = particle;
            if (i != 0) {
                particles[i].position[0] = (float) random() / RAND_MAX * box_length;
                particles[i].position[1] = (float) random() / RAND_MAX * box_length;
                particles[i].velocity[0] = (float) random() / RAND_MAX;
                particles[i].velocity[1] = (float) random() / RAND_MAX;
                particles[i].id = particles[i-1].id + 1;
                //particles[i].charge = -1 * particles[i-1].charge;
            }
        }
}

int main( int argc, char* args[] ) {
	if ( !init() ) {
		printf( "Failed to initialize!\n" );
        return 0;
	}

    init_arraylist(particles, NUM_PARTICLES);

    Particle** part = (Particle**) particles;

    int quit = 0;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_QUIT )
                quit = 1;

        tick(part, dt, NUM_PARTICLES);
        draw(part, NUM_PARTICLES);
        
        usleep(1000000 * dt); //microseconds
    }

	close_sdl();

	return 0;
}