
#pragma once

#include <Math/Polygon.h>

namespace Factory {

class Rect : public Polygon
{
public:
    Vec2 m_vOrigin;
    Vec2 m_vSize;
    
    Rect() : m_vOrigin(Vec2()), m_vSize(Vec2()) {}
    Rect(const Vec2 vOrigin, const Vec2 vSize) : m_vOrigin(vOrigin), m_vSize(vSize) {}
    Rect(const float fX, const float fY, const float fWidth, const float fHeight)
    : m_vOrigin(Vec2(fX, fY)), m_vSize(Vec2(fWidth, fHeight)) {}
};

}