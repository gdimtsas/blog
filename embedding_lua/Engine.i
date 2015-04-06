%module Engine
%{
#include <vector>
#include "Component.h"
#include "TransformationComponent.h"
#include "Entity.h"
#include "Engine.h"
  %}

%include "stl.i"
%template(VectorComponent) std::vector<Engine::Component*>;
%nodefaultctor;

namespace Engine
{
  class Component
  {
  };

  class TransformationComponent : public Component
  {
  public:
    TransformationComponent(float x, float y, float z);

    int x, y, z;
  };

  class Entity
  {
  public:
    Entity(unsigned int id);

    void addComponent(Component* component);
    const std::vector<Component*>& getComponents();

    unsigned int id;
  };

  class Engine
  {
  public:
    void addEntity(Entity* entity);
    const std::vector<Entity*>& getEntities();
  };
}
