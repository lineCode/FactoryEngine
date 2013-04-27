
#pragma once

namespace ftr {
        
//
// Formats primitive data for GL
//
class Primitive
{
public:
    enum Type {
        kNone = 0,
        kLine,
        kPoint,
        kRect,
        kTriangle,
        kPolygon
    };
    
    Primitive(): mIsInvalid(true) {}
    virtual ~Primitive() {
        if(mRenderData) {
            delete[] mRenderData;
            mRenderData=0;
        }
    }
    
    void Invalidate() { mIsInvalid = true; }
    
    virtual Type type() const { return kNone; }
    char* renderData();
    bool isInvalid() const { return mIsInvalid; }
    
protected:
    virtual char* CreateRenderData() { return NULL; };

    char* mRenderData;
private:
    bool mIsInvalid;
    
};


struct Vertex {
    Vec3 vec;
    Color4f color;
};
    
    
class LinePrimitive : public Primitive
{
public:
    struct Data {
        Vertex vertices[2];
        GLubyte indices[2];
    };
    
    LinePrimitive() {}
    virtual ~LinePrimitive() {}
    
    Type type() const { return kLine; }
    Vec3 mBegin;
    Vec3 mEnd;
    Color4f color;
protected:
    char* CreateRenderData();
    
private:
    
};

}

