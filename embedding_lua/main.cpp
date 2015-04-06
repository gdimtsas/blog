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
  Engine::Entity entity(1);

  Engine::TransformationComponent tc;
  entity.addComponent(&tc);

  engine.addEntity(&entity);

  //

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
  return 0;
}
