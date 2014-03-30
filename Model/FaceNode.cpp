
#include <Model/FaceNode.h>
#include <Model/LineNode.h>
#include <Model/PointNode.h>
#include <Processing/PointNodeIterator.h>
#include <Model/Edge.h>


namespace ftr {
    
FaceNode::FaceNode(std::vector<Edge*>& edges)
{
    
    assert(edges.size() > 2);
    for (int i = 0; i < edges.size()-1; ++i) {
        Edge* currentEdge = edges[i]->twin();
        Edge* nextEdge = edges[i+1];
        OrderAscending(*nextEdge, *currentEdge);
    }
    OrderAscending(*edges.front(), *edges.back()->twin());
    assert(IsValid(edges));
    BoundByLoopWithEdge(*edges.front());
}
    
void FaceNode::OrderAscending(Edge& edge1, Edge& edge2)
{
    assert(edge1.originNode() == edge2.originNode());
    PointNode* currentNode = edge1.originNode();
    currentNode->Move(edge2, currentNode->IteratorFromEdge(&edge1));
}
    
bool FaceNode::IsValid(std::vector<Edge*>& edges) const
{
    for(int i = 0; i < edges.size()-1; i++) {
        if (edges[i]->next() != edges[i+1]) {
            return false;
        }
    }
    if (edges.back()->next() != edges.front()) {
        return false;
    }
    return true;
}
    
bool FaceNode::IsValid() const
{
    int counter = 0;
    Edge* currentEdge = mOuterEdge;
    do {
        if (!currentEdge->next()) {
            return false;
        }
        currentEdge = currentEdge->next();
        counter++;
    } while ((currentEdge != mOuterEdge) && (counter < 1000));
    
    return currentEdge == mOuterEdge && (counter > 2);
}

    
FaceNode::FaceNode()
{
    
}

void FaceNode::Render(Layer& layer)
{
    Node::Render(layer);
    mPolygonPrimitive.mColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    Edge* currentEdge = mOuterEdge;
    do {
        mPolygonPrimitive.mVec.push_back(currentEdge->origin());
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
    mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    layer.AddPrimitive(mPolygonPrimitive);
}

#pragma mark - Instance
    
void FaceNode::BoundByLoopWithEdge(Edge& outerEdge)
{
    mOuterEdge = &outerEdge;
    MarkIncidentFaceInLoopWithEdge(outerEdge);
}
    
void FaceNode::AddHoleBoundedByLoopWithEdge(Edge& innerEdge)
{
    mInnerEdges.push_back(&innerEdge);
    MarkIncidentFaceInLoopWithEdge(innerEdge);
}
    
void FaceNode::MarkIncidentFaceInLoopWithEdge(Edge& edge)
{
    Edge* currentEdge = &edge;
    do {
        currentEdge->mIncidentFace = this;
        printf("Mark %s\n", currentEdge->Name().c_str());
        currentEdge = currentEdge->next();
    } while ( currentEdge->IsFree() );
}

std::string FaceNode::Description() const
{
    std::string description = "";
    Edge* currentEdge = mOuterEdge;
    while (currentEdge->next() && (currentEdge->next() != mOuterEdge)) {
        currentEdge = currentEdge->next();
        description += currentEdge->originNode()->mName + "-";
    }
    description += currentEdge->next()->originNode()->mName;
    return description;
}

}
