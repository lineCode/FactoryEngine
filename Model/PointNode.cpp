
#include <Model/PointNode.h>
#include <Main/Log.h>


namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mIsActive(false)
{
    
}

PointNode::PointNode(Vec3 origin)
:mOrigin(origin)
{
    PointNode();
}

void PointNode::Transform(const Mat4& m4Transformation)
{
    mOrigin *= m4Transformation;
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void PointNode::Render(Layer& layer)
{
    Node::Render(layer);
    primitive.mPosition = mOrigin;
    primitive.mColor.set(1.0f, 0.0f, 0.0f, 1.0f);
    primitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(primitive);
}
    
}

