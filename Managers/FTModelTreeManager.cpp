
#include <Managers/FTModelTreeManager.h>
#include <Model/FTPoint.h>


FTModelTreeManager::FTModelTreeManager()
{
    m_pOctree = new FTOctree(FTBox(O5Vec3(0.0f, 0.0f, 0.0f), O5Vec3(8.0f, 8.0f, 8.0f)));
}

FTModelTreeManager::~FTModelTreeManager()
{
    FT_DELETE(m_pOctree);
}

#pragma mark Instance

void FTModelTreeManager::SetRootNode(FTNode *pRootNode)
{
    m_pRootNode = pRootNode;
}

void FTModelTreeManager::AddNode(FTNode* pNode)
{
    if (pNode->Type() == FTNode::kPoint) {
        m_pOctree->InsertPoint(static_cast<FTPoint*>(pNode));
    }
}

void FTModelTreeManager::UpdateNode(FTNode* pNode)
{
    if (pNode->Type() == FTNode::kPoint) {
        m_pOctree->UpdatePoint(static_cast<FTPoint*>(pNode));
    }
}

void FTModelTreeManager::RemoveNode(FTNode* pNode)
{
    if (pNode->Type() == FTNode::kPoint) {
        m_pOctree->RemovePoint(static_cast<FTPoint*>(pNode));
    }
    FTNode* pSupernode = pNode->Supernode();
    assert(pSupernode);
    pSupernode->RemoveNode(pNode);
}

