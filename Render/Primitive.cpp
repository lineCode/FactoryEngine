
#include <Render/Primitive.h>
#include <Main/GLError.h>
#include <Geometry/Polygon.h>
#include <Geometry/Triangle.h>

namespace ftr {
    
Primitive::Primitive() :
    mIsInvalid(true),
    mOptions(kUseNone),
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0)
{
    
}

Primitive::~Primitive()
{
    ClearRenderData();
}
    
void Primitive::ClearRenderData()
{
    if(mRenderData) {
        delete[] mRenderData;
        mRenderData=NULL;
        glDeleteBuffers(mBuffersCount, mBuffers);
        glDeleteVertexArrays(1, &mVertexArrayObjectId);
        
    }
}


char* Primitive::renderData(ShadingInterface& shadingInterface) {
    if (mIsInvalid) {
        ClearRenderData();
        mRenderData = CreateRenderData(shadingInterface);
        mIsInvalid = false;
    }
    return mRenderData;
}
    
void Primitive::setOption(Option option, bool value)
{
    if (value) {
        mOptions |= static_cast<unsigned int>(option);
    } else {
        mOptions &= ~(static_cast<unsigned int>(option));
    }
}
    
    
char* PointPrimitive::CreateRenderData()
{
    PointPrimitive::Data* data = reinterpret_cast<PointPrimitive::Data*>(new char[sizeof(PointPrimitive::Data)]);
    data->indices[0] = 0;
    data->vertices[0].vec = glm::vec4(mPosition.x,mPosition.y, mPosition.z, 0.0f);
    data->vertices[0].color = mColor;
    return reinterpret_cast<char*>(data);
}
        
char* LinePrimitive::CreateRenderData(ShadingInterface& shadingInterface)
{    
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(new char[sizeof(LinePrimitive::Data)]);
    data->vertices[0] = glm::vec4(mBegin.x,mBegin.y, mBegin.z, 1.0f);
    data->vertices[1] = glm::vec4(mEnd.x,mEnd.y, mEnd.z, 1.0f);
    data->colors[0] = mColor;
    data->colors[1] = mColor;
    
    const GLuint colorLoc = shadingInterface.colorLocation();
    const GLuint vertexLoc = shadingInterface.vertexLocation();
    
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    mBuffersCount = 2;
    glGenBuffers(mBuffersCount, mBuffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2, data->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2, data->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    return reinterpret_cast<char*>(data);
}
    
PolygonPrimitive::~PolygonPrimitive()
{
    FT_DELETE_VECTOR(mSubpolygons)
}
    
char* PolygonPrimitive::CreateRenderData(ShadingInterface& shadingInterface)
{
    if (Triangulate() < 2) {
        PolygonPrimitive::Data* data = reinterpret_cast<PolygonPrimitive::Data*>(new char[sizeof(PolygonPrimitive::Data)]);
        
        data->vertices[0] = glm::vec4(mVec[0], 1.0f);
        data->vertices[1] = glm::vec4(mVec[1], 1.0f);
        data->vertices[2] = glm::vec4(mVec[2], 1.0f);
        
        AssignSurfaceNormals(data);
        for(int i = 0; i < 3; ++i) {
            data->colors[i] = mColor;
        }
        
        for(int i = 0; i < 3; ++i) {
            data->pickingColors[i] = mPickingColor;
        }
        
        
        const GLuint vertexLoc = shadingInterface.vertexLocation();
        const GLuint normalLoc = shadingInterface.normalLocation();
        const GLuint colorLoc = ShadingInterface::kColorAttributeIndex;
        const GLuint pickingColorLoc = ShadingInterface::kPickingColorAttributeIndex;
        
        glGenVertexArrays(1, &mVertexArrayObjectId);
        glBindVertexArray(mVertexArrayObjectId);
        
        mBuffersCount = 4;
        glGenBuffers(mBuffersCount, mBuffers);
        
        glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3, data->vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(vertexLoc);
        glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3, data->normals, GL_STATIC_DRAW);
        glEnableVertexAttribArray(normalLoc);
        glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, mBuffers[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3, data->colors, GL_STATIC_DRAW);
        glEnableVertexAttribArray(colorLoc);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, mBuffers[3]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3, data->pickingColors, GL_STATIC_DRAW);
        glEnableVertexAttribArray(pickingColorLoc);
        glVertexAttribPointer(pickingColorLoc, 4, GL_FLOAT, 0, 0, 0);
        return reinterpret_cast<char*>(data);
    }
    return NULL;
}
    
int PolygonPrimitive::Triangulate()
{
    if (mVec.size() > 3) {
        FT_DELETE_VECTOR(mSubpolygons)
        Polygon polygon(mVec);
        polygon.Triangulate();
        for (auto &triangle : polygon.GetTriangles()) {
            PolygonPrimitive* primitive = new PolygonPrimitive(((Triangle*)triangle)->GetPoints());
            primitive->mColor = mColor;
            primitive->mPickingColor = mPickingColor;
            mSubpolygons.push_back(primitive);
        }
        return static_cast<int>(mSubpolygons.size());
    }
    return 1;
}
    
void PolygonPrimitive::AssignSurfaceNormals(PolygonPrimitive::Data* data)
{
    glm::vec4 normal = glm::vec4(0.0f);
    static const int vertexCount = 3;
    for (int i = 0; i < vertexCount; i++) {
        glm::vec4& current = data->vertices[i];
        glm::vec4& next = data->vertices[(i+1)%vertexCount];
        normal.x = normal.x + (current.y - next.y) * (current.z + next.z);
        normal.y = normal.y + (current.z - next.z) * (current.x + next.x);
        normal.z = normal.z + (current.x - next.x) * (current.y + next.y);
    }
    normal = glm::normalize(normal);
    for (int i = 0; i < vertexCount+1; i++) {
        data->normals[i] = normal;
    }

}


}