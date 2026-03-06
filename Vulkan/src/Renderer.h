#pragma once
#include "IRenderer.h"
#include "Instance.h"
#include "Validation.h"


class Renderer : public IRenderer {
public:
    Renderer();

    bool Initialize(HWND hwnd, HINSTANCE hInstance) override;
    void Shutdown() override;
private:
    Validation validation_; 
    std::vector<const char*> extensions_;
    Instance instance_;
    
};
