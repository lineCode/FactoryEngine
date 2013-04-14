

#pragma once

#include <Model/Node.h>
#include <Math/Geometry.h>
#include <Math/Polygon.h>

namespace ftr {

class  ModelManager;

class RectangleInteraction : public Node
{
public:
    
    
    RectangleInteraction(ModelManager& rModelManager);
    virtual ~RectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void SetOrigin(const Vec3& vOrigin);
    void SetCurrent(const Vec3& vCurrent);
    
    
private:
    Polygon m_cPolygon;
    Rectangle3 m_sRect3;
    ModelManager& m_rModelManager;
    bool m_bActive;
};
    
}

