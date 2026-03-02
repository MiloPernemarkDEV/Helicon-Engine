#pragma once
#include "RendDefines.h"

namespace rend
{
    class RENDERER_API IRenderer
    {
    public:
        virtual void hcInitializeRenderer() = 0;
        virtual ~IRenderer() = default;
    };

    RENDERER_API IRenderer* hcCreateRenderer();
}