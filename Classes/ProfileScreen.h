//
// Created by Fedor Shubin on 6/16/14.
//

#ifndef __ProfileScreen_H_
#define __ProfileScreen_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Cocos2dxProfile.h"
#include "CCReward.h"
#include "MuffinRushAssets.h"

class ProfileScreen : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    ProfileScreen():
            shareButton(NULL),
            storyButton(NULL),
            uploadButton(NULL),
            loginButton(NULL),
            logoutButton(NULL),
            loginReward(NULL),
            shareReward(NULL),
            uploadReward(NULL),
            likePageReward(NULL),
            screenshotPath("")
            {}
    virtual bool init();

    CREATE_FUNC(ProfileScreen);

    virtual ~ProfileScreen();

    void onClicked(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    
private:
    
    cocos2d::ui::Button *shareButton;
    cocos2d::ui::Button *storyButton;
    cocos2d::ui::Button *uploadButton;
    cocos2d::ui::Button *loginButton;
    cocos2d::ui::Button *logoutButton;
    soomla::CCReward *loginReward;
    soomla::CCReward *shareReward;
    soomla::CCReward *uploadReward;
    soomla::CCReward *likePageReward;
    std::string screenshotPath;

    float relativeX(float designX, float screenWidth);
    float relativeY(float designY, float screenHeight);
    cocos2d::ui::Button *createActionButton(cocos2d::ui::Layout *parent,
                                            const std::string &normalImage,
                                            const std::string &selectedImage ,
                                            const std::string &disableImage,
                                            const std::string &title,
                                            float posY,
                                            int actionTag, float scaleX, float scaleY, const cocos2d::Size &visibleSize);
    std::string saveScreenshot() const;
    void screenshotSavedCallback(float dt);
    void setLoggedInState();
};


#endif //__ProfileScreen_H_
