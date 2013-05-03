
#include <Model/LineNode.h>

namespace ftr {

LineNode::LineNode(PointNode* startPoint, PointNode* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
{}

#pragma mark - Instance


void LineNode::Render(Layer& layer)
{
    Node::Render(layer);
    if (mStartPoint) {
        mStartPoint->Render(layer);
    }
    if (mEndPoint) {
        mEndPoint->Render(layer);
    }
    
    linePrimitive.mBegin = mStartPoint->mOrigin;
    linePrimitive.mEnd = mEndPoint->mOrigin;
    linePrimitive.color.set(1.0f, 1.0f, 1.0f);
    linePrimitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(linePrimitive);
}

void LineNode::Transform(const Mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    
}



