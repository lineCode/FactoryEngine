
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>
#include <Render/LineBatch.h>

namespace ftr {
    
void LineRenderer::Begin(Batch& batch)
{
    PrimitiveRenderer::Begin(batch);
}
    
void LineRenderer::Render(Batch& batch)
{
    LineBatch& lineBatch = reinterpret_cast<LineBatch&>(batch);
    lineBatch.CreateRenderData(mShadingInterface);
    assert(!lineBatch.IsZombie()); // Invalidating line during rendering
    if (lineBatch.size()) {
        glBindVertexArray(lineBatch.vertexArrayObjectId());
        glDrawArrays(GL_LINES, 0, 2*lineBatch.size());
        glGetError();
    }
}


void LineRenderer::End(Batch& batch)
{
    PrimitiveRenderer::End(batch);
 
}

}
