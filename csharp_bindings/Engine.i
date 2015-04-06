%module Engine
%{
#include <vector>
  %}

%include "stl.i"
%template(VectorComponent) std::vector<Component*>;

class Component
{
public:
  Component();
  virtual ~Component();
};

class TransformationComponent : public Component
{
public:
  TransformationComponent();
  ~TransformationComponent();

  int x, y, z;
};

class Entity
{
public:
  Entity();
  ~Entity();

  void addComponent(Component* component);
  std::vector<Component*> getComponents();
};
