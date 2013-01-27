
#include <Model/FTPoint.h>
#include <Interaction/FTLineInteraction.h>
#include <Managers/FTModelManager.h>

FTLineInteraction::FTLineInteraction(FTModelManager& rModelManager)
    :m_rModelManager(rModelManager)
    ,m_bActive(false)
    ,m_pStartPoint(NULL)
    ,m_pEndPoint(NULL)
{}

#pragma mark Instance

void FTLineInteraction::Render()
{
    FTNode::Render();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        glVertex3d(m_vStart.m_fX,
                   m_vStart.m_fY,
                   m_vStart.m_fZ);
        glVertex3d(m_vEnd.m_fX,
                   m_vEnd.m_fY,
                   m_vEnd.m_fZ);
    }
    glEnd();
}

void FTLineInteraction::Begin()
{
    if (!m_bActive) {
        m_bActive = true;
        m_rModelManager.SelectedNode()->AddNode(this);
        m_pEndPoint = NULL;
        m_pStartPoint = NULL;
        m_vEnd = O5Vec3();
        m_vStart = O5Vec3();
    }
}

void FTLineInteraction::Step()
{
    if (m_bActive) {
        m_bActive = false;
        m_rModelManager.SelectedNode()->RemoveNode(this);
        if (!m_pStartPoint) {
            m_pStartPoint = m_rModelManager.CreatePoint(m_vStart);
        }
        if (!m_pEndPoint) {
            m_pEndPoint = m_rModelManager.CreatePoint(m_vEnd);
        }l
        m_rModelManager.CreateLine(m_pStartPoint, m_pEndPoint);
        m_pStartPoint = m_pEndPoint;
        m_pEndPoint = NULL;
        
    }
}

void FTLineInteraction::End()
{
    m_bActive = false;
}

void FTLineInteraction::SetEnd(O5Vec3 vEnd)
{
    FTPoint* pNearPoint = m_rModelManager.NearestPointToCenterInSphere(FTSphere(vEnd, 0.5f));
    if (pNearPoint) {
        m_vEnd = pNearPoint->m_vOrigin;
        m_pEndPoint = pNearPoint;
    } else {
        m_vEnd = vEnd;
        m_pEndPoint = NULL;
    }
}

void FTLineInteraction::SetStart(O5Vec3 vStart)
{
    FTPoint* pNearPoint = m_rModelManager.NearestPointToCenterInSphere(FTSphere(vStart, 0.5f));
    if (pNearPoint) {
        m_vStart = pNearPoint->m_vOrigin;
        m_pStartPoint = pNearPoint;
    } else {
        m_vStart = vStart;
        m_pStartPoint = NULL;
    }
}
