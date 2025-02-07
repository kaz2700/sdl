#include <SDL2/SDL.h>
#include "artist.h"
#include <stdio.h>

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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

void close_sdl() {
	SDL_DestroyWindow( window );
	window = NULL;

	SDL_Quit();
}

float* translate_position(float* position) {
    float x = (1 - (box_length - position[0])) * SCREEN_WIDTH;
    float y = (box_length - position[1]) * SCREEN_HEIGHT;

    static float translated_position[2];

    translated_position[0] = x;
    translated_position[1] = y;

    return translated_position;
}

void draw(Particle particles[], int num_of_particles){
    //clear screen
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //choose draw color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = 0; i < num_of_particles; i++) {
        drawParticle(particles[i].position, particles[i].radius * SCREEN_WIDTH/box_length);
    }

    SDL_RenderPresent(renderer);
}

void drawParticle(float* position, float radius) {
    float* translated_position = translate_position(position);
    float h;
    for(int i = -radius; i <= radius; i++) {
        h = sqrt( pow(radius, 2) - pow(i, 2));
        for(int j = -h; j <= h; j++)
            SDL_RenderDrawPoint(renderer, translated_position[0] + i, translated_position[1] + j);
    }
}