
#include "SdlContext.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>

SdlContext::SdlContext() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(
            std::string("SDL_INIT failed: ") + SDL_GetError()
        );
    }
}
SdlContext::~SdlContext() {
    SDL_Quit();
}
