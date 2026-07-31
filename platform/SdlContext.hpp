
#pragma once

class SdlContext {
public:
    SdlContext();
    ~SdlContext();

    // delete copy constructor
    SdlContext(const SdlContext&) = delete;
    // delete assignment operator
    SdlContext& operator=(const SdlContext&) = delete;

};
