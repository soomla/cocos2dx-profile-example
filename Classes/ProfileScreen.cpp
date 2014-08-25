//
// Created by Simon Grinberg on 24/08/14.
//

#include "ProfileScreen.h"
#include "MainScene.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define LOGIN_BUTTON_TAG 0
#define STATUS_BUTTON_TAG 1
#define STORY_BUTTON_TAG 2
#define UPLOAD_BUTTON_TAG 3
#define LOGOUT_BUTTON_TAG 4

#define DESIGN_WIDTH 640.0f
#define DESIGN_HEIGHT 1136.0f

cocos2d::Scene *ProfileScreen::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ProfileScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool ProfileScreen::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Layout *layout = Layout::create();

    float vShift = visibleSize.height;
    
    ImageView *background = ui::ImageView::create("profile/BG.png");
    background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    layout->addChild(background);
    
    float scaleX = visibleSize.width / background->getSize().width;
    float scaleY = visibleSize.height / background->getSize().height;
    
    background->setScale(scaleX, scaleY);
    
    ImageView *header = ui::ImageView::create("profile/Headline.png");
    header->setAnchorPoint(Vec2(0.0f, 1.0f));
    header->setScale(scaleX, scaleY);
    header->setPosition(Vec2(0.0f, vShift));
    layout->addChild(header);
    vShift -= header->getSize().height * scaleY;
    
    vShift -= relativeY(70.0f, visibleSize.height);
    
    shareButton = createActionButton(layout,
                                     "profile/BTN-Share-Normal.png", "profile/BTN-Share-Press.png", "profile/BTN-Share-Disable.png", "I Love SOOMLA!",
                                vShift, STATUS_BUTTON_TAG, scaleX, scaleY, visibleSize);
    
    vShift -= shareButton->getSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    storyButton = createActionButton(layout,
                                     "profile/BTN-ShareStory-Normal.png", "profile/BTN-ShareStory-Press.png", "profile/BTN-ShareStory-Disable.png", "I Love SOOMLA!",
                                vShift, STATUS_BUTTON_TAG, scaleX, scaleY, visibleSize);
    
    vShift -= storyButton->getSize().height * scaleY;
    vShift -= relativeY(60.0f, visibleSize.height);
    
    uploadButton = createActionButton(layout,
                                      "profile/BTN-Upload-Normal.png", "profile/BTN-Upload-Press.png", "profile/BTN-Upload-Disable.png", "I Love SOOMLA!",
                                vShift, STATUS_BUTTON_TAG, scaleX, scaleY, visibleSize);
    
    vShift -= uploadButton->getSize().height * scaleY;
    vShift -= relativeY(150.0f, visibleSize.height);
    
    loginButton = ui::Button::create("profile/BTN-Connect.png", "profile/BTN-Connect-Press.png", "profile/BTN-Connect.png");
    loginButton->setActionTag(LOGIN_BUTTON_TAG);
    loginButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    loginButton->setScale(scaleX, scaleY);
    loginButton->setPosition(Vec2(relativeX(30.0f, visibleSize.width), vShift));
    
    loginButton->setTouchEnabled(true);
    loginButton->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(loginButton);
    
    logoutButton = ui::Button::create("profile/BTN-LogOut.png", "profile/BTN-LogOut-Press.png", "profile/BTN-LogOut.png");
    logoutButton->setActionTag(LOGOUT_BUTTON_TAG);
    logoutButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    logoutButton->setScale(scaleX, scaleY);
    logoutButton->setPosition(Vec2(relativeX(30.0f, visibleSize.width), vShift));
    
    logoutButton->setVisible(false);
    logoutButton->setTouchEnabled(true);
    logoutButton->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(logoutButton);
    
    _logText = ui::Text::create();
    _logText->retain();
    _logText->setString("<Nothing here>");
    _logText->setPosition(Vec2(visibleSize.width / 2.0f, _logText->getSize().height / 2));
    layout->addChild(_logText);

    this->addChild(layout);

    std::function<void(EventCustom *)> handleLoginFinished = [this](EventCustom *event) {
        logoutButton->setVisible(true);
        loginButton->setVisible(false);
        
        shareButton->setEnabled(true);
        shareButton->setBright(true);
        
        storyButton->setEnabled(true);
        storyButton->setBright(true);
        
        uploadButton->setEnabled(true);
        uploadButton->setBright(true);
        
        soomla::CCError *profileError = nullptr;
        soomla::CCProfileController::getInstance()->getFeed(soomla::FACEBOOK, nullptr, &profileError);
//        soomla::CCProfileController::getInstance()->getContacts(soomla::FACEBOOK, nullptr, &profileError);
    };
    
    std::function<void(EventCustom *)> handleLogoutFinished = [this](EventCustom *event) {
        logoutButton->setVisible(false);
        loginButton->setVisible(true);
        
        shareButton->setEnabled(false);
        shareButton->setBright(false);
        
        storyButton->setEnabled(false);
        storyButton->setBright(false);
        
        uploadButton->setEnabled(false);
        uploadButton->setBright(false);
    };
    
    std::function<void(EventCustom *)> handleProfileUpdatedFinished = [this](EventCustom *event) {
        soomla::CCUserProfile *userProfile = (soomla::CCUserProfile *)(event->getUserData());
        
        log("%s %s has logged in", userProfile->getFirstName()->getCString(), userProfile->getLastName()->getCString());
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_LOGIN_FINISHED, handleLoginFinished),
                                                                 this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED, handleProfileUpdatedFinished),
                                                                 this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerCustom::create(soomla::CCProfileConsts::EVENT_LOGOUT_FINISHED, handleLogoutFinished),
                                                                 this);

    return true;
}


ProfileScreen::~ProfileScreen() {
    CC_SAFE_RELEASE(_userText);
    CC_SAFE_RELEASE(_logText);
}

void ProfileScreen::onClicked(cocos2d::Ref *ref, Widget::TouchEventType touchType) {
    if (touchType == Widget::TouchEventType::ENDED) {
        auto sender = static_cast<Widget *>(ref);
        soomla::CCError *profileError = nullptr;
        if (sender->getActionTag() == LOGIN_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->login(soomla::FACEBOOK, &profileError);
        }
        else if (sender->getActionTag() == STATUS_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "My status", nullptr, &profileError);
        }
        else if (sender->getActionTag() == STORY_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "My status", nullptr, &profileError);
        }
        else if (sender->getActionTag() == UPLOAD_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus(soomla::FACEBOOK, "My status", nullptr, &profileError);
        }
        else if (sender->getActionTag() == LOGOUT_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->logout(soomla::FACEBOOK, &profileError);
        }
        else {
            return;
        }
        if (profileError) {
            MessageBox(profileError->getInfo(), "Error");
        }
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
                                                       int actionTag, float scaleX, float scaleY, const Size& visibleSize) {
    
    ImageView *bar = ui::ImageView::create("profile/BG-Bar.png");
    bar->setAnchorPoint(Vec2(0.0f, 1.0f));
    bar->setScale(scaleX, scaleY);
    bar->setPosition(Vec2(relativeX(65.0f, visibleSize.width), posY - (7.0f * scaleY)));
    parent->addChild(bar);
    
    Button *button;
    
    button = ui::Button::create(normalImage, selectedImage, disableImage);
    button->setActionTag(actionTag);
    button->setAnchorPoint(Vec2(0.0f, 1.0f));
    button->setScale(scaleX, scaleY);
    button->setPosition(Vec2(relativeX(50.0f, visibleSize.width), posY));
    
    button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    button->setEnabled(false);
    button->setBright(false);
    
    parent->addChild(button);
    
    return button;
}