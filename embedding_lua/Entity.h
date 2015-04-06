#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Component.h"
#include <vector>

namespace Engine
{
  class Entity
  {
  public:
    Entity(unsigned int id)
    {
      this->id = id;
    }

    ~Entity() {}

    void addComponent(Component* component)
    {
      components.push_back(component);
    }

    const std::vector<Component*>& getComponents() const
    {
      return components;
    }

    unsigned int id;

  private:
    std::vector<Component*> components;
  };
}
#endif
