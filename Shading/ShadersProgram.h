
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadersInput.h>

namespace ftr {

class ShadersProgram
{
public:
    ShadersProgram();
    virtual ~ShadersProgram();
    
    void AttachShader(const Shader& shader);
    void Link();
    void Activate();
    void Deactivate();
    GLint status() const { return mStatus; }
    ShadersInput* shaderInput() const { return mShadersInput; }
        
private:
    typedef std::vector<GLuint> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    
    GLuint mId;
    GLint mStatus;
    
    AttachedVector attachedVector;
    ShadersInput* mShadersInput;
};

}

