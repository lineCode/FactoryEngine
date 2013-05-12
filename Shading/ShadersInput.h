
#pragma once

namespace ftr {

class ShadersInput
{
public:
    struct Input {
        GLuint vertex;
        GLuint color;
        GLuint projMatrix;
        GLuint viewMatrix;
        GLuint rotationMatrix;
        GLuint translationMatrix;
    };
    
    ShadersInput(GLuint programId) : mProgramId(programId) {}
    virtual ~ShadersInput() {}
    void BindOutput();
    void Init();
    
    GLuint AttributeLocation(const std::string& name) const;
    GLuint UniformLocation(const std::string& name) const;
    
    void InputProjectionMatrix(Mat4* matrix);
    void InputViewMatrix(Mat4* matrix);
    void InputRotationMatrix(Mat4* matrix);
    void InputTranslationMatrix(Mat4* matrix);
private:
    
    
    GLuint mProgramId;
    Input mInput;
};
    
}
