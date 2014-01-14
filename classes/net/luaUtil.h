//
//  luaUtil.h
//  coclua
//
//  Created by anan on 12/30/13.
//  Copyright (c) 2013 anan. All rights reserved.
//

#ifndef __luautil__
#define __luautil__
extern "C" {
#include "lua.h"
#include "lauxlib.h"
}
#include "cocos2d.h"
USING_NS_CC;

#define DISPATCHER(l,ref) do{\
    if (!l) {\
        break;\
    }\
    lua_rawgeti(l, LUA_REGISTRYINDEX, ref);\
    if (!lua_istable(l, -1)) {\
        break;\
    }\
    lua_getglobal(l, "pairs");\
    lua_pushvalue(l, -2);\
    lua_pcall(l, 1, 3, 0);\
    lua_pushvalue(l, -3);\
    lua_insert(l, -4);\
    while (true) {\
        lua_pcall(l, 2, 2, 0);\
        if (lua_isnil(l, -1)) {\
            lua_pop(l, 4);\
            break;\
        }\
        
#define DISPATCHER_(l)     lua_pop(l, 1);\
        lua_pushvalue(l, -2);\
        lua_insert(l, -2);\
        lua_pushvalue(l, -4);\
        lua_insert(l, -2);\
    }\
}while(0);\

#define CHECK_STACK(L,name) int name = lua_gettop(L);
#define CHECK_STACK_END(L,name,tag) if(name!=lua_gettop(L))printf("the size of previous lua stack does not match current one on %s\n",tag);

#define PUSH_STACK(L) int __stack_num__ = lua_gettop(L);
#define POP_STACK(L) if(lua_gettop(L)>=__stack_num__){lua_pop(L,lua_gettop(L)-__stack_num__);}else{printf("the size of previous lua stack can't less than current one");}

void object2lua(lua_State*L,Object*obj);
Object* lua2object(lua_State*L,int idx);
int finishRequestForLua(lua_State*L,const char* type,Object*obj,int userData);
int receiveSocketForLua(lua_State*L,Object*obj);
void printStack(lua_State*l);
void addElement(lua_State*L,int*ref);
void removeElement(lua_State*L,int*ref);

#endif
