
#pragma once

namespace ftr {
    
class Vertex;
class FaceNode;
class LineNode;

class Edge
{
public:
    Edge(Vertex& vertexA, Vertex& vertexB);
    virtual ~Edge() {}
    
    Vertex* OtherEnd(const Vertex& vertex) const;
    
    std::vector<FaceNode*> mFaces;
    
    bool IsFull() const;
    size_t Degree() const;
    
    LineNode* mLineNode;
    
    std::string Description() const;
private:
    
    Vertex* mVertexA;
    Vertex* mVertexB;
};
    
}

