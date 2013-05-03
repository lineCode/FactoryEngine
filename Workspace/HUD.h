
#pragma once

#include <Model/Node.h>

namespace ftr {

class HUD : Node
{
public:    
    void Render(Layer& layer);
    void RenderDesktop(Layer& layer);
    
private:
    RectanglePrimitive rectanglePrimitive[6];
    RectanglePrimitive desktopPrimitive;
};

}
