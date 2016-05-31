#include <stdio.h>
#include <string.h>

extern "C" 
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

void luaM_setstring(lua_State *L, const char *index, char *value)
{
    lua_pushstring(L, index);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}
void luaM_setnumber(lua_State *L, const char *index, int value)
{
    lua_pushstring(L, index);
    lua_pushnumber(L, (double)value);
    lua_settable(L, -3);
}
int luaM_getstring(lua_State *L, const char *index, char *value)
{
    lua_pushstring(L, index);
    lua_gettable(L, -2);
    fprintf(stderr,"type[%s]\n", lua_typename(L, lua_type(L, -1)));
    if ( ! lua_isstring(L, -1) )
    {
        lua_pop(L, 1);
        return 0;
    }
    strcpy(value, lua_tostring(L, -1));
    lua_pop(L, 1);
    return 1;
}
int luaM_getnumber(lua_State *L, const char *index)
{
    int result;

    lua_pushstring(L, index);
    lua_gettable(L, -2);
    if ( ! lua_isnumber(L, -1) )
    {
       lua_pop(L,1);
        return 0;
    }
    result = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return result;
}

int main(int argc, char **argv)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    char sTest[512]="<?xml version=\"1.0\" encoding=\"utf-8\" ?><req msg=\"test\"></req>";

    lua_newtable(L);
    luaM_setstring(L, "version", "1.1");
    luaM_setstring(L, "host", "127.0.0.1");
    luaM_setstring(L, "method", "POST");
    luaM_setstring(L, "content", sTest);
    luaM_setnumber(L, "contentlength", strlen(sTest));
    lua_setglobal( L, "server");


    if ( luaL_loadfile(L, "./test.lua") || lua_pcall(L, 0, 0, 0) )
    {
        fprintf(stderr, "can not run loader.lua: %s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_getglobal(L,"server");
    if (!lua_istable(L, -1) )
    {
        fprintf(stderr, "loader.lua data err \n");
       return 1;
    }
    char buf[1024];
    luaM_getstring(L, "content",buf);
    int ret = luaM_getnumber(L, "contentlength");
    fprintf(stderr,"resp content[%d]:\n%s\n", ret, buf);
    memset(buf, 0x0, sizeof(buf));
    luaM_getstring(L, "reasonphrase",buf);
    fprintf(stderr,"resp reasonphrase:\n%s\n",  buf);
    ret = luaM_getnumber(L, "statuscode");
    fprintf(stderr,"resp statuscode:\n%d\n",  ret);

    lua_close(L);

    return 1;
}
