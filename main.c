#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef unsigned char u8;

#include "vec4.h"
#include "model.h"

#include <SDL2/SDL.h>
// Normally SDL2 will redefine the main entry point of the program for Windows applications
// this doesn't seem to play nice with TCC, so we just undefine the redefinition
#ifdef __TINYC__
    #undef main
#endif

#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stderr, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
#define SCREEN_HALF_WIDTH 192
#define SCREEN_HALF_HEIGHT 108



struct {
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Renderer *renderer;
    u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool running;
} state;

struct {
    vec4 pos, rot;
    double len;
} camera;



int main(int argc, char** argv) {
    // Initialize SDL
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());

    // Create an SDL window
    state.window = SDL_CreateWindow(
        "3D Graphics",
        SDL_WINDOWPOS_CENTERED_DISPLAY(0),
        SDL_WINDOWPOS_CENTERED_DISPLAY(0),
        1280, 720, SDL_WINDOW_ALLOW_HIGHDPI
    );
    CHECK_ERROR(state.window == NULL, SDL_GetError());

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_PRESENTVSYNC);    
    CHECK_ERROR(state.renderer == NULL, SDL_GetError());

    // Create a render texture
    state.texture = SDL_CreateTexture(
        state.renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );
    CHECK_ERROR(state.texture == NULL, SDL_GetError());

    SDL_Event event;
    state.running = true;

    camera.pos = camera.rot = (vec4){ 0.0, 0.0, 0.0, 0.0 };
    camera.len = 64.0;


    model m = model_load("house.obj");
    model_free(m);



    while (state.running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.running = false;
                    break;
            }
        }

        // const u8* keystate = SDL_GetKeyboardState(NULL);
        // if ( keystate[SDL_SCANCODE_W] )
        //     player.pos.y += 1;
        // else if ( keystate[SDL_SCANCODE_S] )
        //     player.pos.y -= 1;
        
        // if ( keystate[SDL_SCANCODE_D] )
        //     player.pos.x += 1;
        // else if ( keystate[SDL_SCANCODE_A] )
        //     player.pos.x -= 1;

        memset(state.pixels, 0, sizeof(state.pixels)); // Clear screen

        // Draw here
        for ( int j = 0; j < 10; j++ ) {
            for ( int i = 0; i < 10; i++ ) {
                state.pixels[j*SCREEN_WIDTH + i] = 0xFF0000FF;
            }
        }

        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4); // 4 = sizeof(u32)
        SDL_RenderCopyEx(
            state.renderer, state.texture,
            NULL, NULL, 0.0, NULL, 0
        );
        SDL_RenderPresent(state.renderer);
    }

    // Release resources
    SDL_DestroyTexture(state.texture);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();

    return 0;
}