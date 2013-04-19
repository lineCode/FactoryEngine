
#include <Math/Transformation.h>

namespace ftr {

Mat4 Transformation::Move(const Vec3& vMotion)
{
    return Mat4(Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  Vec4(vMotion.mX, vMotion.mY, vMotion.mZ, 1.0f)
                  );
}

Mat4 Transformation::Rotate(const Vec3& vRadians)
{
    Mat4 mx = Mat4::Identity;
    float cx = cosf(vRadians.mX);
    float sx = sinf(vRadians.mX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    Mat4 my = Mat4::Identity;
    float cy = cosf(vRadians.mY);
    float sy = sinf(vRadians.mY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
    Mat4 mz = Mat4::Identity;
    float cz = cosf(vRadians.mZ);
    float sz = sinf(vRadians.mZ);
    mz[0][0] = cz;
    mz[1][0] = sz;
    mz[0][1] = -sz;
    mz[1][1] = cz;
    return mx*my*mz;
}

Mat4 Transformation::Scale(const Vec3& vScale)
{
    return Mat4(Vec4(vScale.mX, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, vScale.mY, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, vScale.mZ, 0.0f),
                  Vec4(0.0f, 0.0f, 0.0f, 1.0f)
                  );
}

}