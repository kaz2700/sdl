#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
int init();

//Loads media
int loadMedia();

//Frees media and shuts down SDL
void cierra();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

int init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    //Create window

    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    
	gScreenSurface = SDL_GetWindowSurface( gWindow );
    return 1;
}

int loadMedia() {

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "image.bmp" );
    if( gHelloWorld == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        return 0;
    }

    return 1;
}

void cierra()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if( !init() ) {
        printf( "Failed to initialize!\n" );
        return 0;
    }

    if( !loadMedia() ) {
        printf("Failed to load media!\n" );
        return 0;
    }

    SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );

    SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

    SDL_UpdateWindowSurface( gWindow );

    //Hack to get window to stay up
    SDL_Event event; 
    int quit = 0; 
    while( !quit ){ 
        while( SDL_PollEvent( &event ) ){ 
            if( event.type == SDL_QUIT ) 
                quit = 1;
        }
    }
    
    cierra();

    return 0;
}