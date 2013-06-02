#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelEditor;

class MoveInteraction : public Node
{
public:
    MoveInteraction(ModelEditor& ModelEditor);
    virtual ~MoveInteraction() {}
    
    void Render();
    void setStart(Vec3 start);
    void setEnd(Vec3 end);
    
private:
    Vec3 mStart;
    Vec3 mEnd;
    Node* mNode;
    ModelEditor& mModelEditor;
    bool mActive;
};
    
}

