#pragma once
#include "RendDefines.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class RENDERER_API IRenderer
{
public:
    virtual bool Initialize(HWND hWnd) = 0;
    virtual ~IRenderer() = default;
    virtual void Shutdown() = 0;
};

RENDERER_API IRenderer* hcCreateRenderer();



