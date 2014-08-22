//
// Created by Fedor Shubin on 6/16/14.
//

#ifndef __ProfileScreen_H_
#define __ProfileScreen_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Cocos2dxProfile.h"

class ProfileScreen : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    ProfileScreen():
            _userText(NULL),
            _logText(NULL)
            {}
    virtual bool init();

    CREATE_FUNC(ProfileScreen);

    virtual ~ProfileScreen();

    void onClicked(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);

    cocos2d::ui::Text *_userText;
    cocos2d::ui::Text *_logText;
};


#endif //__ProfileScreen_H_
