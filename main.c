
#include <SDL2/SDL.h>
#include <stdio.h>
#include "physics.h"
#include "particle.h"
#include <unistd.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int init();
void cierra();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Particle particle1;
float dt = 0.01; //seconds
float time = 0.0; //seconds
float box_length = 1; //meters
	
int init() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return 0;
    }

    window = SDL_CreateWindow( "Fluid Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if ( window == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    
    if ( renderer == NULL ) {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 0;
    }

	return 1;
}

void cierra() {
	SDL_DestroyWindow( window );
	window = NULL;

	SDL_Quit();
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

void translate_coords_and_draw(Particle particle) {
    float x = (1 - (box_length - particle.position[0])) * SCREEN_WIDTH;
    float y = (box_length - particle.position[1]) * SCREEN_HEIGHT;
    SDL_Rect rect = {x, y, particle.radius * 300, particle.radius * 300};

    SDL_RenderDrawRect(renderer, &rect);
}

void draw(){
    //clear screen
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //choose draw color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // for particle in particles
        drawParticle(&particle1);
}

int main( int argc, char* args[] ) {
	if( !init() ) {
		printf( "Failed to initialize!\n" );
        return 0;
	}

    particle1.position[0] = box_length / 3;
    particle1.position[1] = box_length / 2; //meters (we imagine having a 10x10x10cm box)
    particle1.velocity[0] = 5;
    particle1.velocity[1] = 0;
    particle1.radius = 0.05;

    int quit = 0;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_QUIT )
                quit = 1;

        draw();

        //initialize draw color

        gravity(&particle1, &dt);
        check_limits(&particle1);

        translate_coords_and_draw(particle1);
        //SDL_RenderDrawPoint(renderer, (int) particle -> x, particle -> y);
        
        SDL_RenderPresent(renderer);
        time = time + dt;
        usleep(1000000 * dt); //microseconds to seconds * 1000000
    }

	cierra();

	return 0;
}