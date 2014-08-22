//
// Created by Fedor Shubin on 6/16/14.
//

#include "ProfileScreen.h"
#include "MainScene.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCDomainFactory.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define BACK_BUTTON_TAG 0
#define LOGIN_BUTTON_TAG 1
#define STATUS_BUTTON_TAG 2

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

    auto layout = Layout::create();
    layout->setSize(visibleSize);

    Button *button;

    float vShift = visibleSize.height;

    button = ui::Button::create("iphone/back.png");
    button->setActionTag(BACK_BUTTON_TAG);
    button->setScale9Enabled(true);
    button->setSize(Size(0.9f * visibleSize.width, 40.0f));
    vShift -= button->getSize().height;
    button->setPosition(Vec2(0.0f, vShift));
    button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(button);
    vShift -= 8;

    _userText = ui::Text::create();
    _userText->retain();
    _userText->setString("<Nothing here>");
    vShift -= _userText->getSize().height;
    _userText->setPosition(Vec2(visibleSize.width - _userText->getSize().width / 2.0f, vShift));
    layout->addChild(_userText);
    vShift -= 8;

    button = ui::Button::create("iphone/button.png");
    button->setActionTag(LOGIN_BUTTON_TAG);
    button->setScale9Enabled(true);
    button->setTitleText("Login to FB");
    button->setTitleFontSize(32.0f);
    button->setSize(Size(0.9f * visibleSize.width, 40.0f));
    vShift -= button->getSize().height;
    button->setPosition(Vec2(visibleSize.width / 2.0f, vShift));
    button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(button);
    vShift -= 8;

    button = ui::Button::create("iphone/button.png");
    button->setActionTag(STATUS_BUTTON_TAG);
    button->setScale9Enabled(true);
    button->setTitleText("Send status");
    button->setTitleFontSize(32.0f);
    button->setSize(Size(0.9f * visibleSize.width, 40.0f));
    vShift -= button->getSize().height;
    button->setPosition(Vec2(visibleSize.width / 2.0f, vShift));
    button->setTouchEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(ProfileScreen::onClicked, this));
    layout->addChild(button);
    vShift -= 8;

    _logText = ui::Text::create();
    _logText->retain();
    _logText->setString("<Nothing here>");
    _logText->setPosition(Vec2(visibleSize.width / 2.0f, _logText->getSize().height / 2));
    layout->addChild(_logText);

    this->addChild(layout);

    std::function<void(__Dictionary *)> handleError = [this](__Dictionary *parameters) {
        __String *errMsg = dynamic_cast<__String *>(parameters->objectForKey("errorDescription"));
        if (!errMsg) {
            errMsg = __String::create("Cannot extract error date");
        }
        _logText->setString(errMsg->getCString());
    };

    soomla::CCSoomlaEventDispatcher::getInstance()->registerEventHandler(soomla::CCProfileConsts::EVENT_LOGIN_FAILED, handleError);
    soomla::CCSoomlaEventDispatcher::getInstance()->registerEventHandler(soomla::CCProfileConsts::EVENT_LOGOUT_FAILED, handleError);
    soomla::CCSoomlaEventDispatcher::getInstance()->registerEventHandler(soomla::CCProfileConsts::EVENT_GET_CONTACTS_FAILED, handleError);
    soomla::CCSoomlaEventDispatcher::getInstance()->registerEventHandler(soomla::CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED, handleError);

    soomla::CCSoomlaEventDispatcher::getInstance()->registerEventHandler(soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
            [this](__Dictionary *parameters) {
                Ref *userProfileRef = parameters->objectForKey("userProfile");
                __Dictionary *userProfileDict = dynamic_cast<__Dictionary *>(userProfileRef);
                CC_ASSERT(userProfileDict);
                soomla::CCUserProfile *userProfile = dynamic_cast<soomla::CCUserProfile *>(
                        soomla::CCDomainFactory::getInstance()->createWithDictionaryAndType(userProfileDict, soomla::CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE));
                __String *displayName = __String::createWithFormat("%s %s",
                        userProfile->getFirstName() ? userProfile->getFirstName()->getCString() : "(no first name)",
                        userProfile->getLastName() ? userProfile->getLastName()->getCString() : "(no last name)"
                );
                _userText->setString(displayName->getCString());
            }
    );

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
        if (sender->getActionTag() == BACK_BUTTON_TAG) {
            Scene *s = MainScene::getMainScene();
            TransitionScene *transition = TransitionMoveInR::create(0.8f, s);
            Director::getInstance()->replaceScene(transition);
        }
        else if (sender->getActionTag() == LOGIN_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->login("facebook", &profileError);
        }
        else if (sender->getActionTag() == STATUS_BUTTON_TAG) {
            soomla::CCProfileController::getInstance()->updateStatus("facebook", "My status", nullptr, &profileError);
        }
        else {
            return;
        }
        if (profileError) {
            MessageBox(profileError->getInfo(), "Error");
        }
    }
}