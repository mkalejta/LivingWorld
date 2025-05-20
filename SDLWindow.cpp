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
#include <string>
#include <SDL_ttf.h>

const int CELL_SIZE = 40;
const int WIDTH = 15;
const int HEIGHT = 15;
const int BUTTON_WIDTH = 140;
const int BUTTON_HEIGHT = 40;
const int BUTTON_MARGIN = 20;
const int BUTTONS_COUNT = 5;
const int BUTTONS_AREA_WIDTH = BUTTON_WIDTH + 2 * BUTTON_MARGIN;

bool isInside(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w &&
           y >= rect.y && y <= rect.y + rect.h;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text,
                int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void populateWorld(World& world) {
    world.clear();
    world.addOrganism(new Sheep(Position{2, 2}));
    world.addOrganism(new Sheep(Position{11, 3}));
    world.addOrganism(new Cow(Position{5, 5}));
    world.addOrganism(new Cow(Position{6, 10}));
    world.addOrganism(new Wolf(Position{7, 7}));
    world.addOrganism(new Grass(Position{1, 1}));
    world.addOrganism(new Grass(Position{2, 3}));
    world.addOrganism(new Guarana(Position{6, 2}));
    world.addOrganism(new Toadstool(Position{8, 8}));
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Zwiększamy szerokość okna o miejsce na przyciski
    SDL_Window* window = SDL_CreateWindow("LivingWorld SDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH * CELL_SIZE + BUTTONS_AREA_WIDTH, HEIGHT * CELL_SIZE + 30, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 18);
    if (!font) {
        printf("Nie udało się załadować czcionki: %s\n", TTF_GetError());
        return 1;
    }

    // Przyciski pionowo po prawej stronie planszy
    SDL_Rect startBtn  = { WIDTH * CELL_SIZE + BUTTON_MARGIN, 30 + 0 * (BUTTON_HEIGHT + BUTTON_MARGIN), BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect stopBtn   = { WIDTH * CELL_SIZE + BUTTON_MARGIN, 30 + 1 * (BUTTON_HEIGHT + BUTTON_MARGIN), BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect saveBtn   = { WIDTH * CELL_SIZE + BUTTON_MARGIN, 30 + 2 * (BUTTON_HEIGHT + BUTTON_MARGIN), BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect loadBtn   = { WIDTH * CELL_SIZE + BUTTON_MARGIN, 30 + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN), BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect resetBtn  = { WIDTH * CELL_SIZE + BUTTON_MARGIN, 30 + 4 * (BUTTON_HEIGHT + BUTTON_MARGIN), BUTTON_WIDTH, BUTTON_HEIGHT };

    World world(WIDTH, HEIGHT);
    int turnCount = 0;

    populateWorld(world);

    bool running = true, simulating = false;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                if (isInside(x, y, startBtn)) simulating = true;
                if (isInside(x, y, stopBtn)) simulating = false;
                if (isInside(x, y, saveBtn)) world.writeWorld("world.bin");
                if (isInside(x, y, loadBtn)) world.readWorld("world.bin");
                if (isInside(x, y, resetBtn)) {
                    simulating = false;
                    turnCount = 0;
                    populateWorld(world);
                }
            }
        }

        if (simulating) {
            world.makeTurn();
            ++turnCount;
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        // Tura
        SDL_Color black = { 0, 0, 0 };
        renderText(renderer, font, "Tura: " + std::to_string(turnCount),
                   20, 10, black);

        // Plansza
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                SDL_Rect rect = { x * CELL_SIZE, y * CELL_SIZE + 30, CELL_SIZE, CELL_SIZE };
                Organism* org = world.getOrganismAt(Position(x, y));
                if (org && org->isAlive()) {
                    switch (org->draw()) {
                        case 'C': SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255); break;
                        case 'S': SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); break;
                        case 'W': SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break;
                        case 'g': SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); break;
                        case 'G': SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); break;
                        case 'T': SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); break;
                        default:  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); break;
                    }
                } else {
                    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
                }

                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);

                if (org && org->isAlive()) {
                    std::string symbol(1, org->draw());
                    renderText(renderer, font, symbol,
                               x * CELL_SIZE + 12, y * CELL_SIZE + 38, black);
                }
            }
        }

        // Przyciski
        SDL_Color white = { 255, 255, 255 };

        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        SDL_RenderFillRect(renderer, &startBtn);
        renderText(renderer, font, "START", startBtn.x + 25, startBtn.y + 10, white);

        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(renderer, &stopBtn);
        renderText(renderer, font, "STOP", stopBtn.x + 35, stopBtn.y + 10, white);

        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
        SDL_RenderFillRect(renderer, &saveBtn);
        renderText(renderer, font, "ZAPISZ", saveBtn.x + 25, saveBtn.y + 10, white);

        SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);
        SDL_RenderFillRect(renderer, &loadBtn);
        renderText(renderer, font, "WCZYTAJ", loadBtn.x + 20, loadBtn.y + 10, white);

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &resetBtn);
        renderText(renderer, font, "RESET", resetBtn.x + 30, resetBtn.y + 10, white);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
