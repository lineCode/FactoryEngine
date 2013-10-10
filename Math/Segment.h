//
//  Segment.h
//  FactoryEngine
//
//  Created by Edvinas on 10/9/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ftr {

class Segment
{
public:
    Segment() {};
    Segment(const glm::vec3& start, const glm::vec3& end) :
        mStart(start),
        mEnd(end)
    {}
    virtual ~Segment() {}
    
    glm::vec3 mStart;
    glm::vec3 mEnd;
    
    float DistanceFromPoint(const glm::vec3& point);
    float DistanceFromSegment(const Segment& segment);
    float DistanceFromLine(const Segment& segment);
    Segment ShortestSegmentFromLine(const Segment& segment);
    glm::vec3 NearestPoint(const glm::vec3 &testPoint);

};
    
}
