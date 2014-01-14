#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#import <UIKit/UIKit.h>
#import "cocos2d.h"
class AppDelegate : private cocos2d::Application{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    virtual bool applicationDidFinishLaunching();
    
    virtual void applicationDidEnterBackground();
    
    virtual void applicationWillEnterForeground();
};

#endif  // __APP_DELEGATE_H__