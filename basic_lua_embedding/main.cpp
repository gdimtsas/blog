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
  lua_State* L = luaL_newstate();

  // load all lua basic libs (like math, io, string etc...)
  luaL_openlibs(L);

  // execute a lua statement from a string
  luaL_dostring(L, "print('Hello from Lua!')");

  // cleanup lua
  lua_close(L);

  return 0;
}

int luaFunctionCall(int argc, char *argv[])
{
  // initialize lua
  lua_State* L = lua_open();
  luaL_openlibs(L);

  // load the calculator.lua file
  luaL_dofile(L, "calculator.lua");

  // push onto the stack the value of the global "add"
  lua_getglobal(L, "add");

  // push arguments to the stack
  lua_pushnumber(L, 7);
  lua_pushnumber(L, 11);

  // do the call (2 arguments, 1 result)
  int status = lua_call(L, 2, 1);

  // check for errors
  if(status != 0)
    {
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
      return -1;
    }

  // check the result (-1 is the index of the value on the top of the stack)
  if (lua_isnumber(L, -1))
    {
      lua_Number result = lua_tonumber(L, -1);
      std::cout << "Result: " << result << std::endl;
    }

  // pop the result from the stack
  lua_pop(L, 1);

  // cleanup lua
  lua_close(L);

  return 0;
}

extern "C"
{
  int doubleAndTriple(lua_State* L)
  {
    // retrieve the first (and only) argument
    lua_Number n = luaL_checknumber(L, 1);

    // push the first return value
    lua_pushnumber(L, n * 2);
    // and then the second
    lua_pushnumber(L, n * 3);

    // return the number of returned results
    return 2;
  }
}

int cFunctionCall(int argc, char *argv[])
{
  // initialize lua
  lua_State* L = lua_open();
  luaL_openlibs(L);

  // register the doubleAndTriple function under the name "f"
  lua_register(L, "f", doubleAndTriple);

  // call the c function from lua
  luaL_dostring(L, "a, b = f(5);");
  luaL_dostring(L, "print('a = ' .. a)");
  luaL_dostring(L, "print('b = ' .. b)");

  // cleanup lua
  lua_close(L);

  return 0;
}

int main(int argc, char *argv[])
{
  //basic(argc, argv);
  luaFunctionCall(argc, argv);
  //cFunctionCall(argc, argv);
}
