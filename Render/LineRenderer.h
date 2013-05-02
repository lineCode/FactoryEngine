#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class LinePrimitive;

class LineRenderer : public PrimitiveRenderer
{
public:
    LineRenderer() {}
    virtual ~LineRenderer() {}
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive);
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kLine; }
};

}
