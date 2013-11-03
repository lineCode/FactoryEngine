//
//  Vector.h
//  FactoryEngine
//
//  Created by Edvinas on 02/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#pragma once

namespace ftr {

class Vector
{
public:
    virtual ~Vector() {}
    static bool IsCW(const glm::vec3& v1, const glm::vec3& v2);
    static float Angle360(const glm::vec3& v1, const glm::vec3& v2);
    
private:
    static glm::vec3 MostParallelAxis(glm::vec3 v);
    
};
    
}

