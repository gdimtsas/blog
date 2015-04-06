#include <string>
#include <iostream>

#include "Engine.h"
#include "TransformationComponent.h"
#include "Entity.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main(int argc, char *argv[])
{
	Engine::Engine engine;
  Engine::Entity entity(1);

  Engine::TransformationComponent tc;
  entity.addComponent(&tc);

  engine.addEntity(&entity);
  return 0;
}
