
#include "Renderer.hpp"

#include <stdexcept>
#include <string>

Renderer::Renderer(SDL_Window *window, const RendererConfig& config, PhysicsSystem *physicsSystem)
    : physicsSystem_(physicsSystem)
{
        renderer_ = SDL_CreateRenderer(
            window,
            config.index,
            config.flags
            );

        if (renderer_ == nullptr) {
            throw std::runtime_error(
                std::string("SDL_CreateWindow Error: ") + SDL_GetError()
            );
        }
}

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // draw color
    SDL_RenderClear(renderer_); // clear window
    renderPoints();
    renderRectangles();
    SDL_RenderPresent(renderer_); // present renderer
}

void Renderer::renderPoints() {
    for (const PointVisual& point: points_) {
        SDL_SetRenderDrawColor(
            renderer_,
            point.color.r,
            point.color.g,
            point.color.b,
            point.color.a
            );

        SDL_RenderDrawPoint(renderer_, point.x, point.y);
    }
}

void Renderer::renderRectangles() {
    for (const RectangleVisual& rect : rectangles_) {
        SDL_SetRenderDrawColor(
            renderer_,
            rect.color.r,
            rect.color.g,
            rect.color.b,
            rect.color.a
        );
        PhysicsBody body = physicsSystem_->body(rect.body);
        SDL_Rect rectangle = {static_cast<int>(body.position.x), static_cast<int>(body.position.y), static_cast<int>(rect.width), static_cast<int>(rect.height)};

        SDL_RenderDrawRect(renderer_, &rectangle);
    }
}

RectangleHandle Renderer::createRectangle(const PhysicsBodyHandle& body, double width, double height, const SDL_Color& color) {

    const auto index = static_cast<uint32_t>(rectangles_.size());

    RectangleVisual rectangle = {body, width, height, color};

    rectangles_.push_back(rectangle);

    return RectangleHandle{index, 0};
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
}