
#include <SDL2/SDL.h>
#include <stdio.h>
#include "particle.h"
#include <unistd.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init();
void cierra();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Particle particle1;
float dt = 1;
	
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

void gravity(Particle* particle) {
    particle -> y = particle -> y + -10.0*dt;
    printf("%f\n", particle -> y);
}

void check_limits(Particle* particle) {
    if (particle -> y > SCREEN_HEIGHT || particle -> y < 0)
        particle -> y = SCREEN_HEIGHT/2;
}

int main( int argc, char* args[] ) {
	if( !init() ) {
		printf( "Failed to initialize!\n" );
        return 0;
	}
    /*particle = (Particle*)malloc(sizeof(Particle));
    if (particle == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }*/
    particle1.x = SCREEN_WIDTH/2;
    particle1.y = SCREEN_HEIGHT/2;
    particle1.radius = 50;

    int quit = 0;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_QUIT )
                quit = 1;

        //clear screen
        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //initialize draw color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        gravity(&particle1);
        check_limits(&particle1);

        SDL_Rect rect = {particle1.x, particle1.y, particle1.radius, particle1.radius};  
        SDL_RenderDrawRect(renderer, &rect);
        //SDL_RenderDrawPoint(renderer, (int) particle -> x, particle -> y);
        
        SDL_RenderPresent(renderer);

        sleep(dt);
    }

	cierra();

	return 0;
}