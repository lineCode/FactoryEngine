
#pragma once

#include <Model/PointNode.h>
#include <Model/FaceNode.h>

namespace ftr {

class Edge
{
public:
    Edge(PointNode* originNode);
    virtual ~Edge();
    
    FaceNode* mIncidentFace;
    
    const glm::vec3& origin() const { return mOriginNode->mOrigin; }
    
    bool IsCWCountingFrom(const Edge& other) const;
    bool HasSameOrigin(const Edge& other) const { return mOriginNode == other.mOriginNode; }
    bool HasFreeNextEdge() const { return next() && next() && !next()->mIncidentFace; }
    float AngleFrom(const Edge& other) const;
    
    Edge* twin() const { return mTwin; }
    
    Edge* next() const { return mNext; }
    Edge* prev() const { return mPrev; }
    PointNode* originNode() const { return mOriginNode; }
    
    void MakeTwinsWith(Edge* twin);
    void DeleteTwin() { FT_DELETE(mTwin); }
    
    std::string Name() const;
    std::string Description() const;
    
    Edge* CWNeighbourWithSameOrigin();
    void ConnectToNext(Edge* other);
    
    void DoublyConnectCCWOrderedAtOrigin();
    
private:
    
    float CCWAngleFrom(const Edge& other) const;
    void SwitchNextWithPrev();
    

    Edge* mTwin;
    PointNode* mOriginNode;
    Edge* mNext;
    Edge* mPrev;
    
    glm::vec3 Direction() const;

    
};
    

}

