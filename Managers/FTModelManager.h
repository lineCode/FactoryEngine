
#pragma once

#include <Model/FTModelFactory.h>
#include <Model/FTGroup.h>
#include <Managers/FTModelTreeManager.h>

class FTModelManager
{
public:
                            FTModelManager();
                            ~FTModelManager();
    
    FTModelFactory*         ModelFactory() const { return m_pModelFactory; }
    FTModelTreeManager*     ModelTreeManager() const { return  m_pModelTreeManager; }
    FTPoint*                NearestPointToCenterInSphere(const FTSphere& sSphere) const;
    void                    UpdateNode(FTNode* pNode) { m_pModelTreeManager->UpdateNode(pNode); }
    void                    RemoveNode(FTNode* pNode) { m_pModelTreeManager->RemoveNode(pNode); }
    void                    Select(FTNode* pNode);
    unsigned long           Size() { return m_pModelTreeManager->Size(); }
    //
    // Creating
    //
    FTFace*                 CreateFace(O5Vec3 vOrigin, FTFace::FaceType eType);
    FTPoint*                CreatePoint(O5Vec3 vOrigin);
    FTLine*                 CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint);
    
private:
    FTModelFactory*         m_pModelFactory;
    FTModelTreeManager*     m_pModelTreeManager;
    FTGroup*                m_pRootGroup;
    FTNode*                 m_pSelectedNode;
};

