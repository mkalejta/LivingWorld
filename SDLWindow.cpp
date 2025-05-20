#include <SDL.h>
#include "World.h"
#include <thread>
#include <chrono>
#include "Toadstool.h"
#include "Position.h"
#include "Organism.h"
#include "Cow.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Guarana.h"
#include "Grass.h"
#include "Guarana.h"

const int CELL_SIZE = 40;
const int WIDTH = 10;
const int HEIGHT = 10;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("LivingWorld SDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE + 50, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    World world(WIDTH, HEIGHT);

    // Inicjalizacja organizmów
    // Owce
    world.addOrganism(new Sheep(Position{2, 2}));
    world.addOrganism(new Sheep(Position{3, 3}));

    // Krowy
    world.addOrganism(new Cow(Position{5, 5}));
    world.addOrganism(new Cow(Position{6, 6}));

    // Wilk
    world.addOrganism(new Wolf(Position{7, 7}));

    // Trawy
    world.addOrganism(new Grass(Position{1, 1}));
    world.addOrganism(new Grass(Position{2, 3}));

    // Guarana
    world.addOrganism(new Guarana(Position{6, 2}));

    // Muchomor
    world.addOrganism(new Toadstool(Position{8, 8}));

    bool running = true, simulating = false;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_s) simulating = true;
                if (e.key.keysym.sym == SDLK_p) simulating = false;
                if (e.key.keysym.sym == SDLK_q) running = false;
                if (e.key.keysym.sym == SDLK_w) world.writeWorld("world.bin");
                if (e.key.keysym.sym == SDLK_l) { world.readWorld("world.bin"); }
            }
        }
        if (simulating) {
            world.makeTurn();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        // Rysowanie
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                SDL_Rect rect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                Organism* org = world.getOrganismAt(Position(x, y));
                if (org && org->isAlive()) {
                    switch (org->draw()) {
                        case 'C': SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255); break; // Cow
                        case 'S': SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); break; // Sheep
                        case 'W': SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break; // Wolf
                        case 'g': SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); break; // Grass
                        case 'G': SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); break; // Guarana
                        case 'T': SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); break; // Toadstool
                        default:  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); break;
                    }
                } else {
                    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
                }
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}