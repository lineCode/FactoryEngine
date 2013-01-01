
#include "FTLine.h"

FTLine::FTLine(FTPoint* pStartPoint, FTPoint* pEndPoint)
    :m_pStartPoint(pStartPoint)
    ,m_pEndPoint(pEndPoint)
{}

#pragma mark - Instance

void FTLine::Render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    //
    // grind
    //
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        O5Vec3 startVec = m_pStartPoint->GetOrigin();
        O5Vec3 endVec = m_pEndPoint->GetOrigin();
        glVertex3d(startVec.m_fX,
                   startVec.m_fY,
                   startVec.m_fZ);
        glVertex3d(endVec.m_fX,
                   endVec.m_fY,
                   endVec.m_fZ);
    }
    glEnd();
}


