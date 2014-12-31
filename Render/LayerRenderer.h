
#pragma once

#include <Shading/ShadingInterface.h>

namespace ftr {
    
class Layer;
class PrimitiveRenderer;
class Primitive;
class PolygonBatch;

//
// Renders layer primitives
//
class LayerRenderer
{
public:
            LayerRenderer(ShadingInterface& ShadingInterface);
    virtual ~LayerRenderer();
    
    virtual void Render(Layer& layer);
    
    
protected:
    void RenderSublayersRecursively(Layer& layer);
    void AddRenderer(PrimitiveRenderer* primitiveRenderer);
    
    virtual void RenderInternal(Layer& layer);
    
    typedef std::vector<PrimitiveRenderer*> RenderersVector;
    RenderersVector mRenderersVector;
    
    int mDepth;
};

} // ftr