
#include <Geometry/Geometry.h>

#pragma once

namespace ftr {

class Polyline : public Geometry
{
public:
    Polyline() {};
    Polyline(const std::vector<glm::vec3>& points) { mPoints = points; }
    
    void AddPoint(const glm::vec3& point);
    virtual std::vector<glm::vec3>& GetPoints() { return mPoints; }
    
protected:
    
};
    
}

