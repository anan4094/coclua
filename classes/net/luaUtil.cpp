//
//  luaUtil.cpp
//
//  Created by anan on 12/30/13.
//  Copyright (c) 2013 anan. All rights reserved.
//
#include "luaUtil.h"
#include "baseUtil.h"
void object2lua(lua_State*L,Object*obj){
    if (dynamic_cast<Dictionary*>(obj)) {
        lua_newtable(L);
        Dictionary* dir=(Dictionary*)obj;
        Array*b=dir->allKeys();
        for (int i=0; i<b->count(); i++) {
            const char*tmp = ((String*)b->getObjectAtIndex(i))->getCString();
            lua_pushstring(L, tmp);
            object2lua(L,dir->objectForKey(tmp));
            lua_settable(L, -3);
        }
    }else if (dynamic_cast<Array*>(obj)) {
        lua_newtable(L);
        Array* arr=(Array*)obj;
        for (int i=0; i<arr->count(); i++) {
            lua_pushnumber(L, i+1);
            object2lua(L,arr->getObjectAtIndex(i));
            lua_settable(L, -3);
        }
        lua_pushstring(L, "count");
        lua_pushnumber(L, arr->count());
        lua_settable(L, -3);
    }else if(dynamic_cast<String*>(obj)){
        lua_pushstring(L, ((String*)obj)->getCString());
    }else if(dynamic_cast<Integer*>(obj)){
        lua_pushnumber(L, ((Integer*)obj)->getValue());
    }else if(dynamic_cast<Double*>(obj)){
        lua_pushnumber(L, ((Double*)obj)->getValue());
    }else if(dynamic_cast<Float*>(obj)){
        lua_pushnumber(L, ((Float*)obj)->getValue());
    }else if(dynamic_cast<Bool*>(obj)){
        lua_pushboolean(L, ((Bool*)obj)->getValue()?1:0);
    }else{
        lua_pushnil(L);
    }
}
Object* lua2object(lua_State*L,int idx){
    lua_pushvalue(L, idx);
    Object *ret = NULL;
    if (lua_istable(L, -1)) {
        Dictionary*tmp=new Dictionary::Dictionary();
        if (tmp) {
            tmp->init();
        }
        lua_getglobal(L, "pairs");
        lua_pushvalue(L, -2);
        lua_pcall(L, 1, 3, 0);
        lua_pushvalue(L, -3);
        lua_insert(L, -4);
        int count = 0,nc;
        bool isarray = true;
        char numstr[64]={0};
        while (true) {
            lua_pcall(L, 2, 2, 0);
            if (lua_isnil(L, -1)) {
                lua_pop(L, 3);
                break;
            }
            if (lua_type(L, -2) == LUA_TSTRING) {
                tmp->setObject(lua2object(L, -1), lua_tostring(L, -2));
                isarray = false;
            }else{
                nc = lua_tonumber(L, -2);
                if (++count!=nc) {
                    isarray = false;
                }
                sprintf(numstr, "%d",nc);
                tmp->setObject(lua2object(L, -1), numstr);
            }
            lua_pop(L, 1);
            lua_pushvalue(L, -2);
            lua_insert(L, -2);
            lua_pushvalue(L, -4);
            lua_insert(L, -2);
        }
        if (isarray) {
            Array*tmp1 = Array::createWithCapacity(nc);
            for (int i=0; i<nc; i++) {
                sprintf(numstr, "%d",i+1);
                tmp1->addObject(tmp->objectForKey(numstr));
            }
            ret = tmp1;
        }else{
            ret = tmp->autorelease();
        }
    }else if(lua_isstring(L, -1)){
        ret = String::create(lua_tostring(L, -1));
    }else if(lua_isnumber(L, -1)){
        ret = Double::create(lua_tonumber(L, -1));
    }
    lua_pop(L, 1);
    return ret;
}
int finishRequestForLua(lua_State*L,const char* type,Object*obj,int userData){
    if (obj==nullptr) {
        echo("luaUtil","http request object is null\n");
        return -1;
    }
    do{
        if (!L) {
            break;
        }
        char funname[64] = {};
        sprintf(funname, "finished%sRequest", type);
        lua_getglobal(L, "RequestManager");
        if (!lua_istable(L, -1)) {
            echo("luaUtil","request mananer object don't exist\n");
            lua_pop(L, 1);
            break;
        }
        lua_pushstring(L, funname);
        lua_gettable(L,-2);
        if (lua_isfunction(L, -1)) {
            echo("luaUtil","execute %s method for http request\n",funname);
            lua_insert(L, -2);
            lua_pushstring(L, type);
            object2lua(L,obj);
            int param_num = 3;
            if (userData!=LUA_REFNIL) {
                lua_rawgeti(L, LUA_REGISTRYINDEX, userData);
                param_num++;
            }
            if(lua_pcall(L, param_num, 0, 0)){
                echo("luaUtil","http request lua analytic method run error:%s\n",lua_tostring(L, -1));
            }
            return 0;
        }else{
            echo("luaUtil","execute default method for http request on %s\n",type);
            lua_pop(L, 2);
            break;
        }
    }while (0);
    object2lua(L,obj);
    return 1;
}
int receiveSocketForLua(lua_State*L,Object*obj){
    if (obj==nullptr) {
        echo("luaUtil","socket message object is null\n");
        return -1;
    }
    CHECK_STACK(L, aaa)
    do {
        if (!L) {
            break;
        }
        lua_getglobal(L, "RequestManager");
        if (!lua_istable(L, -1)) {
            echo("luaUtil","request mananer object don't exist\n");
            lua_pop(L, 1);
            break;
        }
        lua_pushstring(L, "receiveSocketMessage");
        lua_gettable(L, -2);
        if (lua_isfunction(L, -1)) {
            lua_insert(L, -2);
            object2lua(L,obj);
            if(lua_pcall(L, 2, 0, 0)){
                echo("luaUtil","socket message lua analytic method run error:%s\n",lua_tostring(L, -1));
            }
            CHECK_STACK_END(L, aaa, "receiveSocketForLua1")
            return 0;
        }else{
            echo("luaUtil","execute default method for receive socket message\n");
            lua_pop(L, 2);
            break;
        }
    } while (0);
    CHECK_STACK_END(L, aaa, "receiveSocketForLua0")
    object2lua(L, obj);
    return 1;
}
void addElement(lua_State*l,int*ref){
    CHECK_STACK(l, a)
    if (!l) {
        return;
    }
    if (!lua_istable(l, -1)) {
        return;
    }
    lua_pushstring(l, "___ref___");
    lua_rawget(l, -2);
    if (!lua_isnil(l, -1)) {
        lua_pop(l, 1);
        return;
    }
    lua_pop(l, 1);
    if (*ref == LUA_REFNIL) {
        lua_newtable(l);
        *ref = luaL_ref(l, LUA_REGISTRYINDEX);
    }
    lua_rawgeti(l, LUA_REGISTRYINDEX, *ref);
    lua_pushvalue(l, -2);
    int r = luaL_ref(l, -2);
    printf("add element into table%d by index %d\n",*ref,r);
    lua_pushstring(l, "___ref___");
    lua_pushnumber(l, r);
    lua_rawset(l, -4);
    lua_pop(l, 1);
    CHECK_STACK_END(l, a, "addElement")
}
void removeElement(lua_State*l,int*ref){
    CHECK_STACK(l, a)
    if (!l) {
        return;
    }
    if (!lua_istable(l, -1)) {
        return;
    }
    lua_pushstring(l, "___ref___");
    lua_rawget(l, -2);
    if (lua_type(l, -1)!=LUA_TNUMBER) {
        lua_pop(l, 1);
        CHECK_STACK_END(l, a, "removeElement1")
        return;
    }
    int r=lua_tonumber(l, -1);
    lua_rawgeti(l, LUA_REGISTRYINDEX,*ref);
    if (!lua_istable(l, -1)) {
        lua_pop(l, 2);
        CHECK_STACK_END(l, a, "removeElement2")
        return;
    }
    luaL_unref(l, -1, r);
    lua_pop(l, 2);
    CHECK_STACK_END(l, a, "removeElement3")
}
void printStack(lua_State*l){
    //get number of elements in stack
    int n = lua_gettop(l);
    if (!n) {
        printf("[]\n");
        return;
    }
    printf("[\n");
    for (int i=1; i<=n; i++) {
        int type = lua_type(l, i);
        switch (type) {
            case LUA_TSTRING:
                printf("   index:%d(%d) '%s'\n",i,i-n-1,lua_tostring(l, i));
                break;
            case LUA_TBOOLEAN:
                printf("   index:%d(%d) %s\n",i,i-n-1,lua_toboolean(l, i)?"true":"false");
                break;
            case LUA_TNUMBER:
                printf("   index:%d(%d) %g\n",i,i-n-1,lua_tonumber(l, i));
                break;
            default:
                printf("   index:%d(%d) %s\n",i,i-n-1,lua_typename(l, type));
                break;
        }
    }
    printf("]\n");
}