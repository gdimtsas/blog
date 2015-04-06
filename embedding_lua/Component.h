#ifndef _COMPONENT_H_
#define _COMPONENT_H_

namespace Engine
{
  class Component
  {
  public:
    Component() {}
	virtual ~Component() = 0;
  };

  inline Component::~Component() {}
}

#endif
