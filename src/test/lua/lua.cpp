#include <iostream>


extern "C" 
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

static int average(lua_State *L)
{
    //返回栈中元素的个数  
    int n = lua_gettop(L); 
    double sum = 0;  
    int i;  
    for (i = 1; i <= n; i++)  
    {  
        if (!lua_isnumber(L, i))   
        {  
            lua_pushstring(L, "Incorrect argument to 'average'");  
            lua_error(L);  
        }  
        sum += lua_tonumber(L, i);  
    }
    /* push the average */
    lua_pushnumber(L, sum / n);
    /* push the sum */  
    lua_pushnumber(L, sum);

    /* return the number of results */
    return 2;
}

int luaadd(lua_State* L, int x, int y)
{
    lua_getglobal(L, "add");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    lua_call(L, 2, 1);

    int sum = (int)lua_tonumber(L, -1);

    lua_pop(L, 1);                  

    return sum;
}

int main(int argc, char** agrv)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "average", average);
    luaL_dofile(L, "test.lua");

    lua_getglobal(L,"avg");  
    std::cout<<"avg is:"<<lua_tonumber(L,-1)<<std::endl;  
    lua_pop(L,1);  
    lua_getglobal(L,"sum");  
    std::cout<<"sum is:"<<lua_tonumber(L,-1)<<std::endl;  
    lua_pop(L,1);  

    std::cout<<"add result is:"<<luaadd(L, 10, 15)<<std::endl;

    /* cleanup Lua */
    lua_close(L); 

    return 0;
}
