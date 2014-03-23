
#include <Math/Plane.h>
#include <Utils/Description.h>

namespace ftr {
    
Plane::Plane(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3&  p3) :
mP1(p1), mP2(p2), mP3(p3)
{
    mCross = glm::cross(p2 - p1, p3 - p1);
}
    
bool Plane::Contains(const glm::vec3& p) const
{
    glm::vec3 cross = glm::cross(mP2 - p, mP2 - mP1);
    return glm::isNull(glm::cross(mCross, cross), 0.3f);
//    glm::vec3 crosscross = glm::cross(mCross, cross);
//    float length = glm::length(crosscross);
//    std::cout << length << std::endl;
//    return length < 0.3;
}
    
std::string Plane::Description() const
{
    std::stringstream ss;
    ss << std::endl;
    ss << Description::Desribed(mP1) << std::endl;
    ss << Description::Desribed(mP2) << std::endl;
    ss << Description::Desribed(mP3) << std::endl;
    ss << std::endl;
    return ss.str();
}
    

    
}

