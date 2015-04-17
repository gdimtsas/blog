#include <string>
#include <iostream>

#include "Engine.h"
#include "TransformationComponent.h"
#include "Entity.h"
#include "swig.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

extern "C"
{
  int luaopen_Engine(lua_State* L);
}

int main(int argc, char *argv[])
{
  Engine::Engine engine;
  /*
    for(int i = 1; i < 100; ++i)
	{
    Engine::Entity* entity = new Engine::Entity(i);
    Engine::TransformationComponent*  tc = new Engine::TransformationComponent(i, i, i);
    entity->addComponent(tc);
    engine.addEntity(entity);
	}
  */

  lua_State* state = lua_open();
  luaL_openlibs(state);
  luaopen_Engine(state);

  SWIG_Lua_NewPointerObj(state,
                         &engine,
                         SWIG_TypeQuery(state, "Engine::Engine *"),
                         0);
  lua_setglobal(state, "engine");

  int status = luaL_dofile(state, "Example.lua");
  if(status != 0)
    {
      std::cerr << lua_tostring(state, -1) << std::endl;
      lua_pop(state, 1);
    }

  auto entities = engine.getEntities();
  for(auto entity : entities)
    {
	  std::cout << entity->id << std::endl;
    }
  return 0;
}
