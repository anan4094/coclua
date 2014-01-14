//
//  main.m
//  coclua
//
//  Created by anan on 12/13/13.
//  Copyright (c) 2013 anan. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppController.h"

int main(int argc, char * argv[])
{
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    int retval = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retval;
}
