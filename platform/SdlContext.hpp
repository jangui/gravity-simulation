
#pragma once

class SdlContext {
public:
    SdlContext();
    ~SdlContext();
    SdlContext(const SdlContext&) = delete; // delete copy constructor
    SdlContext& operator=(const SdlContext&) = delete; // delete assignment operator
};
