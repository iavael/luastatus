#ifndef ls_lua_utils_h_
#define ls_lua_utils_h_

#include <lua.h>

#include "compdep.h"

// Traverse a table.
// Before leaving this cycle, call LS_LUA_TRAVERSE_BREAK(L_).
// if StackIndex_ is relative to the top, decrease it by one because the previous key will be
// pushed onto the stack each time lua_next() is called.
#define LS_LUA_TRAVERSE(L_, StackIndex_) \
    for (lua_pushnil(L_); \
         lua_next(L_, (StackIndex_) < 0 ? (StackIndex_) - 1 : (StackIndex_)); \
         lua_pop(L_, 1))

#define LS_LUA_TRAVERSE_KEY   (-2)
#define LS_LUA_TRAVERSE_VALUE (-1)

#define LS_LUA_TRAVERSE_BREAK(L_) lua_pop(L_, 2)

// The behaviour is same as calling lua_getfield(L, -1, key), except that it does not invoke
// metamethods.
LS_INHEADER
void
ls_lua_rawgetf(lua_State *L, const char *key)
{
    lua_pushstring(L, key);
    lua_rawget(L, -2);
}

// The behaviour is same as calling lua_setfield(L, -3, key), except that it does not invoke
// metamethods.
LS_INHEADER
void
ls_lua_rawsetf(lua_State *L, const char *key)
{
    lua_pushstring(L, key);
    lua_insert(L, -2);
    lua_rawset(L, -3);
}

// Pushes the global table onto the stack. The behaviour is same as calling lua_pushglobaltable(L_)
// in Lua >=5.2.
#if LUA_VERSION_NUM >= 502
#   define ls_lua_pushglobaltable lua_pushglobaltable
#else
#   define ls_lua_pushglobaltable(L_) lua_pushvalue(L_, LUA_GLOBALSINDEX)
#endif

#endif
