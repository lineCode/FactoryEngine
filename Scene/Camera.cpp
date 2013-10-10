

#include <Scene/Camera.h>
#include <Main/Log.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Utils/Picker.h>


namespace ftr {
    
const float Camera::kViewportScale = 0.3;

Camera::Camera(const glm::vec3& eyePosition)
    :mShadingInterface(NULL)
{
    mEyePosition = eyePosition;
    mTranslation = glm::vec3();
    mRotation = glm::vec3();
}
    
void Camera::CreateTransformations()
{
    mTransform.view = RotationMatrix() * TranslationMatrix() * InitialMatrix();
    mParameters.modelviewMatrix = mTransform.view;
}
    
glm::mat4 Camera::RotationMatrix()
{
    mPivot = mEyePosition;
    static const glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = mEyePosition;
    forward = glm::normalize(forward);
    glm::vec3 side = glm::normalize(glm::cross(forward, axisY));
    glm::mat4 rotation =
    glm::translate(-mPivot)
    * glm::rotate(mRotation.x, side)
    * glm::rotate(mRotation.y, axisY)
    * glm::translate(mPivot);
    return rotation;
}
    
glm::mat4 Camera::InitialMatrix()
{
    static const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    static const glm::vec3 target = glm::vec3(0.0f);
    return glm::lookAt(mEyePosition, target, up);
}
    
glm::mat4 Camera::TranslationMatrix()
{
   return glm::translate(mTranslation);
}
    
void Camera::CommitTransformations()
{
    if (mShadingInterface) {
        mShadingInterface->InputTransform(mTransform);
    }
}
    
glm::vec3 Camera::RotateVector(const glm::vec3& vec)
{
    static const glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec3 forward = glm::normalize(mEyePosition);
    static glm::vec3 side = glm::normalize(glm::cross(forward, axisY));
    
    glm::vec3 result;
    result = glm::rotate(vec, -mRotation.x, side);
    result = glm::rotate(result, -mRotation.y, axisY);
    return result;
}
    
void Camera::MoveBy(const glm::vec2 deltaMove)
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::normalize(mEyePosition);
    
    up = RotateVector(up);
    forward = RotateVector(forward);
    glm::vec3 side = glm::normalize(glm::cross(up, forward));

    mTranslation += side * deltaMove.x;
    mTranslation += up * deltaMove.y;
}

void Camera::RotateBy(const glm::vec2 deltaRotation)
{
    mRotation.x -= deltaRotation.x;
    mRotation.y += deltaRotation.y;
    
    double ip;
    modf(mRotation.x/360, &ip);
    mRotation.x = mRotation.x - ip*360;
    modf(mRotation.y/360, &ip);
    mRotation.y = mRotation.y - ip*360;
    
}

void Camera::ZoomBy(const float delta, const glm::vec2& toViewportPoint)
{
    glm::vec3 scenePoint = Picker::Scene(toViewportPoint, mParameters);
    glm::vec2 viewportCenter = glm::vec2(mParameters.viewport[2] * 0.5f,
                                         mParameters.viewport[3] * 0.5f);
    const Segment& segment = Picker::RayAtPoint(viewportCenter, mParameters);
    glm::vec3 start = segment.mStart;
    glm::vec3 forward = glm::normalize(scenePoint - start);
    
    float distance = glm::length(scenePoint - start);
    
    static const float speed = 0.01f;
    
    float coef = std::max(0.0f, distance-0.5f) * speed;
    coef = std::min(coef, 0.5f);
    
    float extra = 0.0f;
    if (coef == 0) {
        if (delta > 0) {
            extra = 0.01f;
        }
    }
    
    mTranslation += forward * delta * (coef + extra);
}

void Camera::setProjection(Projection projectionMode)
{
    mProjection = projectionMode;
    switch (projectionMode) {
        case kProjectionPerspective: {
            mTransform.projection = glm::perspective(60.0f, 1.0f, 0.1f, 10000.f);
            
        } break;
        case kProjectionOrthographic: {
            mTransform.projection = glm::perspective(60.0f, 1.0f, 0.1f, 10000.f);;
        } break;
    }
    mParameters.projectionMatrix = mTransform.projection;
}
    
void Camera::setViewport(const  glm::vec4& frame)
{
    float width = fabsf(frame[0] - frame[2]);
    float height = fabsf(frame[1] - frame[3]);
    float size = std::max(width, height);
    glViewport(0.0f, 0.0f, size, size);
    mParameters.viewport =  glm::vec4(glm::vec2(), glm::vec2(size, size));
#ifndef GLES
    mShadingInterface->InputWindowSize(glm::vec2(size, size));
#endif
}
    
}


