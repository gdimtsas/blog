#ifndef _TRANSFORMATION_COMPONENT_H_
#define _TRANSFORMATION_COMPONENT_H_

#include "Component.h"

namespace Engine
{
  class TransformationComponent : public Component
  {
  public:
    TransformationComponent(float x = 0.0f,
                            float y = 0.0f,
                            float z = 0.0f) : Component()
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    virtual ~TransformationComponent() {};

    float x, y, z;
  };
}

#endif
