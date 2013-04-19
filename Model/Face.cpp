
#include <Model/Face.h>
#include <Model/Line.h>
#include <Model/Point.h>
#include <Main/Log.h>

namespace ftr {

Face::Face()
{
    
}


void Face::Render()
{
    Node::Render();
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.5f,0.5f,0.5f);
        glNormal3f(0,-1,0);
        for(auto i = m_vPointsVector.begin(); i != m_vPointsVector.end(); ++i) {
            glVertex3f((*i)->m_vOrigin.mX, (*i)->m_vOrigin.mY, (*i)->m_vOrigin.mZ);
        }
    }
    glEnd();
    
}

#pragma mark - Instance

void Face::SetSize(const Vec3 vSize)
{
    m_vSize = vSize;
}

void Face::SetOrigin(const Vec3 vOrigin)
{
    m_vOrigin = vOrigin;
}


void Face::AddPoint(Point* pPoint)
{
    m_vPointsVector.push_back(pPoint);
}

void Face::AddLine(Line* pLine)
{
    m_vLinesVector.push_back(pLine);
    AddNode(pLine);
}
//
// Checks if point is int the same plane with face.
// Point is in same plane if any three points coordinate in same axes is the same.
//
bool Face::IsInFacePlane(Vec3 vec)
{
    return true;
}
//
// Checks point in the same plane intersection with face
//
bool Face::Contains(Vec3 vec)
{
    return false;
}
//
// Adds cut region to face, should divide into convex polygons
//
void Face::Cut(Face *cutFace)
{
    
}

void Face::Transform(Mat4& m4Transformation)
{
    for(auto i = m_vPointsVector.begin(); i != m_vPointsVector.end(); ++i) {
        (*i)->Transform(m4Transformation);
    }
}

}
