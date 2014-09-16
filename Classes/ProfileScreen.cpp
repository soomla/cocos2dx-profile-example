/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

//
// Created by Simon Grinberg on 24/08/14.
//

#include <time.h>
#include <unistd.h>
#include "ProfileScreen.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCVirtualItemReward.h"
#include "MuffinRushAssets.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define LOGIN_BUTTON_TAG 0
#define STATUS_BUTTON_TAG 1
#define STORY_BUTTON_TAG 2
#define UPLOAD_BUTTON_TAG 3
#define LOGOUT_BUTTON_TAG 4

#define DESIGN_WIDTH 640.0f
#define DESIGN_HEIGHT 1136.0f

cocos2d::CCScene *ProfileScreen::createScene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    CCLayer *layer = ProfileScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool ProfileScreen::init() {
    if (!TouchGroup::init()) {
        return false;
    }
    
    setTouchEnabled(true);
    
    loginReward = soomla::CCVirtualItemReward::create(CCString::create("login_reward"),
                                                      CCString::create("Login Reward"),
                                                      CCBool::create(false), CCInteger::create(100), CCString::create(MUFFIN_CURRENCY_ITEM_ID));
    loginReward->retain();
    
    shareReward = soomla::CCVirtualItemReward::create(CCString::create("share_reward"),
                                                      CCString::create("Share Reward"),
                                                      CCBool::create(false), CCInteger::create(150), CCString::create(MUFFIN_CURRENCY_ITEM_ID));
    shareReward->retain();
    
    uploadReward = soomla::CCVirtualItemReward::create(CCString::create("upload_reward"),
                                                      CCString::create("Upload Reward"),
                                                      CCBool::create(false), CCInteger::create(200), CCString::create(MUFFIN_CURRENCY_ITEM_ID));
    uploadReward->retain();
    
    likePageReward = soomla::CCVirtualItemReward::create(CCString::create("like_page_reward"),
                                                       CCString::create("Like Page Reward"),
                                                       CCBool::create(false), CCInteger::create(300), CCString::create(MUFFIN_CURRENCY_ITEM_ID));
    likePageReward->retain();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    Layout *layout = Layout::create();

    float vShift = visibleSize.height;
    
    ImageView *background = ImageView::create();
    background->loadTexture("profile/BG.png");
    background->setPosition(CCPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    layout->addChild(background);
    
    float scaleX = visibleSize.width / background->getContentSize().width;
    float scaleY = visibleSize.height / background->getContentSize().height;
    
    background->setScale(scaleX, scaleY);
    
    ImageView *header = ImageView::create();
    header->loadTexture("profile/Headline.png");
    header->setAnchorPoint(CCPoint(0.0f, 1.0f));
    header->setScale(scaleX, scaleY);
    header->setPosition(CCPoint(0.0f, vShift));
    layout->addChild(header);
    vShift -= header->getContentSize().height * scaleY;
    
    vShift -= relativeY(70.0f, visibleSize.height);
    
    shareButton = createActionButton(layout,
                                     "profile/BTN-Share-Normal.png", "profile/BTN-Share-Press.png", "profile/BTN-Share-Disable.png", "I Love SOOMLA!",
                                vShift, STATUS_BUTTON_TAG, scaleX, scaleY, visibleSize);
    shareButton->retain();
    
    vShift -= shareButton->getContentSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    storyButton = createActionButton(layout,
                                     "profile/BTN-ShareStory-Normal.png", "profile/BTN-ShareStory-Press.png", "profile/BTN-ShareStory-Disable.png", "Full story of The SOOMBOT!",
                                vShift, STORY_BUTTON_TAG, scaleX, scaleY, visibleSize);
    storyButton->retain();
    
    vShift -= storyButton->getContentSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    uploadButton = createActionButton(layout,
                                      "profile/BTN-Upload-Normal.png", "profile/BTN-Upload-Press.png", "profile/BTN-Upload-Disable.png", "Screenshot",
                                vShift, UPLOAD_BUTTON_TAG, scaleX, scaleY, visibleSize);
    uploadButton->retain();
    
    vShift -= uploadButton->getContentSize().height * scaleY;
    vShift -= relativeY(150.0f, visibleSize.height);
    
    loginButton = ui::Button::create();
    loginButton->loadTextures("profile/BTN-Connect.png", "profile/BTN-Connect-Press.png", "profile/BTN-Connect.png");
    loginButton->retain();
    loginButton->setActionTag(LOGIN_BUTTON_TAG);
    loginButton->setAnchorPoint(CCPoint(0.0f, 1.0f));
    loginButton->setScale(scaleX, scaleY);
    loginButton->setPosition(CCPoint(relativeX(30.0f, visibleSize.width), vShift));
    
    loginButton->setTouchEnabled(true);
    loginButton->addTouchEventListener(this, toucheventselector(ProfileScreen::onClicked));
    layout->addChild(loginButton);
    
    logoutButton = ui::Button::create();
    logoutButton->loadTextures("profile/BTN-LogOut.png", "profile/BTN-LogOut-Press.png", "profile/BTN-LogOut.png");
    logoutButton->retain();
    logoutButton->setActionTag(LOGOUT_BUTTON_TAG);
    logoutButton->setAnchorPoint(CCPoint(0.0f, 1.0f));
    logoutButton->setScale(scaleX, scaleY);
    logoutButton->setPosition(CCPoint(relativeX(30.0f, visibleSize.width), vShift));
    
    logoutButton->setVisible(false);
    logoutButton->setTouchEnabled(true);
    logoutButton->setEnabled(false);
    logoutButton->addTouchEventListener(this, toucheventselector(ProfileScreen::onClicked));
    layout->addChild(logoutButton);

    this->addWidget(layout);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileScreen::onLoginFinished),
                                                                  soomla::CCProfileConsts::EVENT_LOGIN_FINISHED, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileScreen::onProfileUpdated),
                                                                  soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileScreen::onLogoutFinished),
                                                                  soomla::CCProfileConsts::EVENT_LOGOUT_FINISHED, NULL);
    
    soomla::CCError *profileError = NULL;
    bool isLoggedIn =  soomla::CCProfileController::getInstance()->isLoggedIn(soomla::FACEBOOK, &profileError);
    if (profileError) {
        CCMessageBox(profileError->getInfo(), "Error");
    }
    else {
        if (isLoggedIn) {
            setLoggedInState();
        }
    }

    return true;
}


ProfileScreen::~ProfileScreen() {
    CC_SAFE_DELETE(shareButton);
    CC_SAFE_DELETE(storyButton);
    CC_SAFE_DELETE(uploadButton);
    CC_SAFE_DELETE(loginButton);
    CC_SAFE_DELETE(logoutButton);
}

void ProfileScreen::onLoginFinished(CCObject* obj) {
    this->setLoggedInState();
    
    soomla::CCError *profileError = NULL;
    soomla::CCProfileController::getInstance()->like(soomla::FACEBOOK, "The.SOOMLA.Project", likePageReward, &profileError);
    soomla::CCProfileController::getInstance()->getFeed(soomla::FACEBOOK, NULL, &profileError);
    soomla::CCProfileController::getInstance()->getContacts(soomla::FACEBOOK, NULL, &profileError);
}

void ProfileScreen::onLogoutFinished(CCObject* obj) {
    logoutButton->setVisible(false);
    logoutButton->setEnabled(false);
    loginButton->setVisible(true);
    loginButton->setEnabled(true);
    
    shareButton->setTouchEnabled(false);
    shareButton->setBright(false);
    
    storyButton->setTouchEnabled(false);
    storyButton->setBright(false);
    
    uploadButton->setTouchEnabled(false);
    uploadButton->setBright(false);
}

void ProfileScreen::onProfileUpdated(CCObject* obj) {
    soomla::CCUserProfile *userProfile = (soomla::CCUserProfile *)(obj);
    
    CCLOG("%s %s has logged in", userProfile->getFirstName()->getCString(), userProfile->getLastName()->getCString());
}

void ProfileScreen::onClicked(cocos2d::CCObject *ref, TouchEventType touchType) {
    if (touchType == TOUCH_EVENT_ENDED) {
        Widget *sender = static_cast<Widget *>(ref);
        soomla::CCError *profileError = NULL;
        if (sender->getActionTag() == LOGIN_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->login(soomla::FACEBOOK, loginReward, &profileError);
            
            // TEST open rating page
            soomla::CCProfileController::getInstance()->openAppRatingPage(&profileError);
        }
        else if (sender->getActionTag() == STATUS_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "I love SOOMLA! http://www.soom.la", shareReward, &profileError);
        }
        else if (sender->getActionTag() == STORY_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStory(soomla::FACEBOOK,
                                                                    "This is the story of a very strong and brave SOOMBOT on his jurney from SOOMBOTIA to a far away galaxy. That galaxy contains a blue planet where all human game developers love to eat food spiced with marshmallow.",
                                                                    "The story of SOOMBOT (Profile Test App)",
                                                                    "SOOMBOT Story",
                                                                    "DESCRIPTION",
                                                                    "http://about.soom.la/soombots",
                                                                    "http://about.soom.la/wp-content/uploads/2014/05/330x268-spockbot.png",
                                                                    NULL,
                                                                    &profileError);
        }
        else if (sender->getActionTag() == UPLOAD_BUTTON_TAG) {
            screenshotPath = saveScreenshot();
            // Cocos2dx does not have a callback for saveToFile so creating a hacky solution
            this->scheduleOnce(schedule_selector(ProfileScreen::screenshotSavedCallback), 1.0f);
        }
        else if (sender->getActionTag() == LOGOUT_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->logout(soomla::FACEBOOK, &profileError);
        }
        else {
            return;
        }
        if (profileError) {
            CCMessageBox(profileError->getInfo(), "Error");
        }
    }
}

void ProfileScreen::screenshotSavedCallback(float dt) {
    soomla::CCError *profileError = NULL;
    soomla::CCProfileController::getInstance()->uploadImage(soomla::FACEBOOK,
                                                            "I love SOOMLA! http://www.soom.la",
                                                            screenshotPath.c_str(),
                                                            uploadReward,
                                                            &profileError);
    if (profileError) {
        CCMessageBox(profileError->getInfo(), "Error");
    }
}

float ProfileScreen::relativeX(float designX, float screenWidth) {
    return (designX / DESIGN_WIDTH) * screenWidth;
}

float ProfileScreen::relativeY(float designY, float screenHeight) {
    return (designY / DESIGN_HEIGHT) * screenHeight;
}

cocos2d::ui::Button *ProfileScreen::createActionButton(cocos2d::ui::Layout *parent,
                                                       const std::string &normalImage,
                                                       const std::string& selectedImage ,
                                                       const std::string& disableImage,
                                                       const std::string& title,
                                                       float posY,
                                                       int actionTag, float scaleX, float scaleY, const CCSize& visibleSize) {
    
    ImageView *bar = ImageView::create();
    bar->loadTexture("profile/BG-Bar.png");
    bar->setAnchorPoint(CCPoint(0.0f, 1.0f));
    bar->setScale(scaleX, scaleY);
    bar->setPosition(CCPoint(relativeX(65.0f, visibleSize.width), posY - (7.0f * scaleY)));
    parent->addChild(bar);
    
    Button *button;
    
    button = Button::create();
    button->loadTextures(normalImage.c_str(), selectedImage.c_str(), disableImage.c_str());
    button->setActionTag(actionTag);
    button->setAnchorPoint(CCPoint(0.0f, 1.0f));
    button->setScale(scaleX, scaleY);
    button->setPosition(CCPoint(relativeX(50.0f, visibleSize.width), posY));
    
    button->setTouchEnabled(true);
    button->addTouchEventListener(this, toucheventselector(ProfileScreen::onClicked));
//    button->setEnabled(false);
    button->setBright(false);
    
    parent->addChild(button);
    
    Label *label = Label::create();
    label->setFontName("GoodDog.otf");
    label->setText(title);
    label->setFontSize(20);
    label->setColor(ccBLACK);
    label->setAnchorPoint(CCPoint(0.0f, 1.0f));
    label->setSize(CCSize(relativeX(280.0f, visibleSize.width), relativeY(100.0f, visibleSize.height)));
    label->ignoreContentAdaptWithSize(false);
    label->setTextHorizontalAlignment(kCCTextAlignmentLeft);
    label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    label->setScale(scaleX, scaleY);
    label->setPosition(CCPoint(relativeX(270.0f, visibleSize.width), posY - (12.0f * scaleY)));
    parent->addChild(label);
    
    return button;
}

std::string ProfileScreen::saveScreenshot() const {
    CCSize screen = CCDirector::sharedDirector()->getWinSize();
    
    CCRenderTexture *tex = CCRenderTexture::create(int(screen.width), int(screen.height));
    tex->retain();
    
    tex->setPosition(CCPoint(screen.width/2.0f, screen.height/2.0f));
    
    tex->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    tex->end();
    
    CCString *path = CCString::createWithFormat("%s%d.png", "screenshot_", int(time(0)));
    tex->saveToFile(path->getCString(), kCCImageFormatPNG);
    
    return CCFileUtils::sharedFileUtils()->getWritablePath() + path->getCString();
}

void ProfileScreen::setLoggedInState() {
    logoutButton->setVisible(true);
    logoutButton->setEnabled(true);
    loginButton->setVisible(false);
    loginButton->setEnabled(false);
    
    shareButton->setTouchEnabled(true);
    shareButton->setBright(true);
    
    storyButton->setTouchEnabled(true);
    storyButton->setBright(true);
    
    uploadButton->setTouchEnabled(true);
    uploadButton->setBright(true);
}