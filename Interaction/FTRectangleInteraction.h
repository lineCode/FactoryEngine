

#pragma once

#include <Model/FTNode.h>

class  FTModelManager;

class FTRectangleInteraction : public FTNode
{
public:
    FTRectangleInteraction(FTModelManager& rModelManager);
    virtual ~FTRectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void SetSize(const O5Vec3 vSize);
    const O5Vec3& Size() const { return m_vSize; }
    void SetOrigin(const O5Vec3 vOrigin);
    const O5Vec3& Origin() const { return m_vOrigin; }
    
private:
    O5Vec3 m_vOrigin;
    O5Vec3 m_vSize;
    FTModelManager& m_rModelManager;
    bool m_bActive;
};

