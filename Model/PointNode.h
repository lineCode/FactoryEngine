
#pragma once

#include <Model/Node.h>
#include <Model/Octree.h>

namespace ftr {

class PointNodeIterator;
class Edge;
    
class PointNode : public Node
{
public:
    typedef PointNodeIterator Iterator;
    
    static const float c_fR;
    PointNode();
    PointNode(glm::vec3 origin);
    virtual ~PointNode();
    
    glm::vec3 mOrigin;
    
    virtual void Render(Layer& layer);
    virtual NodeType Type() const { return kPoint; }
    virtual void Transform(const glm::mat4& m4Transformation);
    Octree::Leaf* OctreeLeaf() const { return mOctreeLeaf; }
    void setOctreeLeaf(Octree::Leaf* leaf) { mOctreeLeaf = leaf; }
    void setActive(bool active) { mIsActive = active; }
    bool Active() const { return mIsActive; }
    
    Edge* ConnectTo(PointNode* other);
    Edge* mEdge;
    Edge* Edge() const { return mEdge; }
    ftr::Edge* FindOutgoingFreeEdge() const;
    
    ftr::Edge* Begin() const;
    ftr::Edge* End() const;
    
    
    std::string mName;
    
private:
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
    PointPrimitive primitive;
};
    
}

