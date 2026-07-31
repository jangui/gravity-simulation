#pragma once

class Renderer {
public:
    Renderer();
    ~Renderer();

    // delete copy constructor
    Renderer(const Renderer&) = delete;
    // delete assignment operator
    Renderer& operator=(const Renderer&) = delete;
};

