
#include "Application.hpp"

#include <vector>

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

Application::Application()
    : physics_(),
    sdl_(),
    window_(WindowConfig{}),
    renderer_(window_.getWindow(), RendererConfig{}, &physics_)
    {}

void Application::run() {
    // initialize bodies and points
    srand(time(0));
    createBody(1000, 10, 600, 450, 0, 0, {255, 0, 0, 255});
    int maxSize = 5;
    int minSize = 1;
    int spawns = 12;
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = 10;
        double x = 0;
        double y = randomInRange(0, 900);
        double vx = randomInRange(0, 75);
        double vy = randomInRange(-75, 75);
        SDL_Color color = {static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), 255};
        createBody(mass, radius, x, y, vx, vy, color);
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = 10;
        double x = 1200;
        double y = randomInRange(0, 900);
        double vx = randomInRange(-75, 0);
        double vy = randomInRange(-75, 75);
        SDL_Color color = {static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), 255};
        createBody(mass, radius, x, y, vx, vy, color);
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = 10;
        double x = randomInRange(0, 1200);
        double y = 0;
        double vx = randomInRange(-75, 75);
        double vy = randomInRange(0, 75);
        SDL_Color color = {static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), 255};
        createBody(mass, radius, x, y, vx, vy, color);
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = 10;
        double x = randomInRange(0, 1200);
        double y = 900;
        double vx = randomInRange(-75, 75);
        double vy = randomInRange(-75, 0);
        SDL_Color color = {static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), static_cast<Uint8>(randomInRange(0, 255)), 255};
        createBody(mass, radius, x, y, vx, vy, color);
    }

    // fps
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    double frameStart;
    double frameStartOld = 0;
    int frameTime;

    // Main loop
    bool running = true;
    while (running) {
        frameStart = SDL_GetTicks();
        double deltaTime = (frameStart - frameStartOld) / 1000;
        frameStartOld = frameStart;


        // Handle Events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Updating
        physics_.updateBodies(deltaTime);

        // Render
        renderer_.render();

        // handle fps
        frameTime = static_cast<int>(SDL_GetTicks() - frameStart);
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up resources
    SDL_Quit();
}

void Application::createBody(double mass, double radius, double x, double y, double vx, double vy, SDL_Color color) {
    const auto bodyHandle = physics_.createBody({x,y}, {vx,vy}, mass);
    renderer_.createRectangle(bodyHandle, static_cast<int>(radius), static_cast<int>(radius), color);
}

Application::~Application() {}
