
#include <Lighting/LightingModel.h>

namespace ftr {

LightingModel::LightingModel()
{
    
}

LightingModel::~LightingModel()
{
    
}
    
Light::Data* LightingModel::Data() const
{
    assert(mLightsVector.size() <= mShadersInput->mSettings.lightsCount);
    Light::Data* data = reinterpret_cast<Light::Data*>(new char[ModelDataSize()]);
    for (int i = 0; i < mLightsVector.size(); ++i) {
        data[i] = mLightsVector[i]->mData;
    }
    for (size_t i = mLightsVector.size(); i < mShadersInput->mSettings.lightsCount; ++i) {
        data[i] = Light::Data();
    }
    return data;
}
    
size_t LightingModel::ModelDataSize() const
{
    return sizeof(Light::Data) * mShadersInput->mSettings.lightsCount;
}
    
void LightingModel::SendDataToShader()
{
    mShadersInput->mSettings.lightsCount = static_cast<int>(mLightsVector.size());
    mShadersInput->InputLight(*Data());
}
        
}

