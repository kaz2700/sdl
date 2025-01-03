
#include <SDL2/SDL.h>
#include <stdio.h>
#include "particle.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init();
void cierra();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
	
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

int main( int argc, char* args[] ) {
	if( !init() ) {
		printf( "Failed to initialize!\n" );
        return 0;
	}

    Particle part;
    part.x = SCREEN_WIDTH/2;

    int quit = 0;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                quit = 1;
            }
        }
        //clear screen
        SDL_SetRenderDrawColor(renderer,
                   0, 0, 0,
                   255);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer,
                   255, 255, 255,
                   255);
        SDL_RenderDrawPoint(renderer, (int) part.x, SCREEN_HEIGHT/2);
        

        SDL_RenderPresent(renderer);
        part.x += 0.1;
    }

	cierra();

	return 0;
}