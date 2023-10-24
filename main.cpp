#include <SDL.h>
#include <iostream>
#include <list>

struct Color {
    int r, g, b, a;
};

class Body {
public:
    int x, y; // position
    double accumulatedX, accumulatedY;
    double vx, vy; // velocity
    double mass;
    int radius;
    Color color;

    Body(double mass, int radius, int x, int y, double vx, double vy, const Color& color)
        : mass(mass), radius(radius), x(x), y(y), vx(vx), vy(vy), color(color), accumulatedX(0), accumulatedY(0) {}

    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);  // R, G, B, A
        SDL_Rect rect = { x, y,radius, radius }; // x, y, w, h
        SDL_RenderDrawRect(renderer, &rect);
    }

    void update(std::list<Body*>& bodies, double deltaTime) {
        //double g = 6.674 * pow(10, -11); // gravitational constant
        double g = 10000;

        // acceleration
        double ax = 0.0;
        double ay = 0.0;

        // apply forces from other bodies and check for collisions
        for (auto it = bodies.begin(); it != bodies.end();) {
            Body *other = *it;
            if (other == this) { ++it; continue; }

            // calculate distance between two bodies
            double dx = other->x - x;
            double dy = other->y - y;
            double d = sqrt((dx * dx) + (dy * dy)) + 1e-10;  // add a small value to prevent division by zero

            // check if colliding
            if (d <= (other->radius + radius) ) {
               // merge other body to current body
               merge(*other);

                // delete other
                delete other; other = nullptr;

               // remove other from list
               it = bodies.erase(it); // returns incremented iterator after erasing
               continue;
            }
            // manually increment iterator due to logic when merging bodies
            ++it;

            // calculate gravitational force
            double fg = (g * other->mass) / (d * d * d);
            ax += fg * (other->x - x);
            ay += fg * (other->y - y);
        }

        // update velocity
        vx += ax * deltaTime;
        vy += ay * deltaTime;

        // update position with accumulated changes
        accumulatedX += vx * deltaTime;
        accumulatedY += vy * deltaTime;

        x += static_cast<int>(accumulatedX);
        y += static_cast<int>(accumulatedY);

        // reset accumulated changes
        accumulatedX -= static_cast<int>(accumulatedX);
        accumulatedY -= static_cast<int>(accumulatedY);
    }

    void merge(const Body& other) {
        mass += other.mass;
        radius += other.radius;
        vx = 0;
        vy = 0;
    }
};

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Orbits", 100, 100, 1200, 900, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // initialize bodies
    srand(time(0));
    std::list<Body*> bodies;
    bodies.push_back(new Body(1000, 10, 600, 450, 0, 0, {255, 0, 0, 255}));
    int maxSize = 5;
    int minSize = 1;
    int spawns = 12;
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = mass / 100.0;
        double x = 0;
        double y = randomInRange(0, 900);
        double vx = randomInRange(0, 75);
        double vy = randomInRange(-75, 75);
        Color color = {randomInRange(0, 255), randomInRange(0, 255), randomInRange(0, 255), 255};
        bodies.push_back(new Body(mass, radius, x, y, vx, vy, color));
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = mass / 100.0;
        double x = 1200;
        double y = randomInRange(0, 900);
        double vx = randomInRange(-75, 0);
        double vy = randomInRange(-75, 75);
        Color color = {randomInRange(0, 255), randomInRange(0, 255), randomInRange(0, 255), 255};
        bodies.push_back(new Body(mass, radius, x, y, vx, vy, color));
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = mass / 100.0;
        double x = randomInRange(0, 1200);
        double y = 0;
        double vx = randomInRange(-75, 75);
        double vy = randomInRange(0, 75);
        Color color = {randomInRange(0, 255), randomInRange(0, 255), randomInRange(0, 255), 255};
        bodies.push_back(new Body(mass, radius, x, y, vx, vy, color));
    }
    for (int i = 0; i < spawns; ++i) {
        double mass = randomInRange(minSize, maxSize);
        double radius = mass / 100.0;
        double x = randomInRange(0, 1200);
        double y = 900;
        double vx = randomInRange(-75, 75);
        double vy = randomInRange(-75, 0);
        Color color = {randomInRange(0, 255), randomInRange(0, 255), randomInRange(0, 255), 255};
        bodies.push_back(new Body(mass, radius, x, y, vx, vy, color));
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
        for (auto *body : bodies) {
            body->update(bodies, deltaTime);
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // draw color
        SDL_RenderClear(renderer); // clear window
        // Render Objects
        for (auto *body : bodies) {
            body->render(renderer);
        }
        SDL_RenderPresent(renderer); // present renderer

        // handle fps
        frameTime = static_cast<int>(SDL_GetTicks() - frameStart);
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up resources
    for (auto *body : bodies) {
        delete body;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
