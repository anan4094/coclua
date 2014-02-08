//
//  baseUtil.cpp
//  coclua
//
//  Created by anan on 1/4/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#include "baseUtil.h"

void echo(const char*tag,const char*pszFormat, ...){
    printf("%s:",tag);
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

std::string UrlEncode(const std::string& szToEncode)
{
    std::string src = szToEncode;
    char hex[] = "0123456789ABCDEF";
    std:: string dst;
    
    for (size_t i = 0; i < src.size(); ++i)
    {
        unsigned char cc = src[i];
        if (isascii(cc))
        {
            if (cc == ' ')
            {
                dst += "%20";
            }
            else
                dst += cc;
        }
        else
        {
            unsigned char c = static_cast<unsigned char>(src[i]);
            dst += '%';
            dst += hex[c / 16];
            dst += hex[c % 16];
            
        }
    }
    return dst;
}

static int lua_echo(lua_State*l){
    if (lua_gettop(l)==2) {
        if (lua_type(l, 1)==LUA_TSTRING&&lua_type(l, 2)==LUA_TSTRING) {
            printf("%s:%s\n",lua_tostring(l, 1),lua_tostring(l, 2));
        }
    }
    return 0;
}

int lua_auto_util(lua_State*l){
    static const luaL_Reg reqlib [] = {
        {"echo", lua_echo},
        {NULL, NULL}  /* sentinel */
    };
    int i=0;
    while (reqlib[i].name) {
        lua_pushcfunction(l, reqlib[i].func);
        lua_setglobal(l, reqlib[i].name);
        i++;
    }
    return 0;
}