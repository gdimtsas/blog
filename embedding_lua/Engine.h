#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Entity.h"
#include <vector>

namespace Engine
{
  class Engine
  {
  public:
    Engine() {}

    void addEntity(Entity* entity)
    {
      entities.push_back(entity);
    }

    const std::vector<Entity*>& getEntities()
    {
      return entities;
    }

  private:
    std::vector<Entity*> entities;
  };
}

#endif
