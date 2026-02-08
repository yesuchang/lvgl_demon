#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("=== SDL2 Test Program ===\n");
    printf("Initializing SDL2...\n");
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    printf("SDL2 initialized successfully!\n");
    
    SDL_Window* window = SDL_CreateWindow("SDL2 Test Window",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         800, 600,
                                         SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    printf("Window created successfully\n");
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    printf("Renderer created successfully\n");
    printf("You should see a window with colored rectangles.\n");
    printf("Close the window or press ESC to exit.\n");
    
    int quit = 0;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
        
        // 绘制蓝色背景
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);
        
        // 绘制红色矩形
        SDL_Rect rect1 = {100, 100, 200, 150};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect1);
        
        // 绘制绿色矩形
        SDL_Rect rect2 = {400, 200, 150, 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect2);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("Application exited successfully\n");
    return 0;
}