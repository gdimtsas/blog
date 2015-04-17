#include <iostream>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int basic(int argc, char *argv[])
{
  // initialize lua
  lua_State* L = lua_open();

  // load all lua basic libs, like math, io, string etc...
  luaL_openlibs(L);

  int status = 0;

  // execute a lua statement from a string
  status = luaL_dostring(L, "print('Hello from Lua!')");

  // or from a file
  status = luaL_dofile(L, "example.lua");
  if(status != 0)
    {
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
    }

  // cleanup lua
  lua_close(L);

  return 0;
}

int functionCall(int argc, char *argv[])
{
  // initialize lua
  lua_State* L = lua_open();

  // load all lua basic libs, like math, io, string etc...
  luaL_openlibs(L);

  // load the example.lua file
  int status = luaL_dofile(L, "example.lua");
  if(status != 0)
    {
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
      return -1;
    }

  lua_getglobal(L, "add");
  if(!lua_isfunction(L, -1))
    {
      lua_pop(L, 1);
      return -1;
    }

  // push arguments to the stack
  lua_pushnumber(L, 7);
  lua_pushnumber(L, 11);

  // do the call (2 arguments, 1 result)
  status = lua_pcall(L, 2, 1, 0);
  if(status != 0)
    {
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
      return -1;
    }

  // retrieve result
  if (!lua_isnumber(L, -1))
    {
      return -1;
    }

  int result = lua_tonumber(L, -1);
  std::cout << "Result: " << result << std::endl;

  // pop the result from the stack
  lua_pop(L, 1);

  // cleanup lua
  lua_close(L);

  return 0;
}

int main(int argc, char *argv[])
{
  basic(argc, argv);
  functionCall(argc, argv);
}
