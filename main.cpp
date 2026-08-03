
#include <iostream>

#include <SDL.h>

#include "Application.hpp"

int main(int argc, char *argv[]) {
    try {
        Application app;
        app.run();
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
