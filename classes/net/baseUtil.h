//
//  baseUtil.h
//  coclua
//
//  Created by anan on 1/4/14.
//  Copyright (c) 2014 anan. All rights reserved.
//

#ifndef __coclua__baseUtil__
#define __coclua__baseUtil__

#include <stdio.h>
#include <stdarg.h>
#include "cocos2d.h"
USING_NS_CC;

void echo(const char*tag,const char*pszFormat, ...);
std::string UrlEncode(const std::string& szToEncode);

#endif /* defined(__coclua__baseUtil__) */
