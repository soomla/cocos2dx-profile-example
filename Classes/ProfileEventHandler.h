//
// Created by Fedor Shubin on 6/14/14.
//


#include "CCProfileEventHandler.h"

#ifndef __ProfileEventHandler_H_
#define __ProfileEventHandler_H_


class ProfileEventHandler: public soomla::CCProfileEventHandler {

public:
    virtual void onLoginFailed(cocos2d::__String *errorDescription);

    virtual void onLoginFinished(soomla::CCUserProfile *userProfile);

    virtual void onLoginStarted(cocos2d::__String *provider);

    virtual void onLogoutFailed(cocos2d::__String *errorDescription);

    virtual void onLogoutFinished(soomla::CCUserProfile *userProfile);

    virtual void onLogoutStarted(cocos2d::__String *provider);

    virtual void onGetContactsFailed(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription);

    virtual void onGetContactsFinished(cocos2d::__String *socialActionType, cocos2d::__Array *contactsDict);

    virtual void onGetContactsStarted(cocos2d::__String *socialActionType);

    virtual void onSocialActionFailedEvent(cocos2d::__String *socialActionType, cocos2d::__String *errorDescription);

    virtual void onSocialActionFinishedEvent(cocos2d::__String *socialActionType);

    virtual void onSocialActionStartedEvent(cocos2d::__String *socialActionType);

    virtual void onLoginCancelledEvent();

    virtual void onRewardGivenEvent(soomla::CCReward *reward);

    virtual void onUserProfileUpdatedEvent(soomla::CCUserProfile *userProfile);
};


#endif //__ProfileEventHandler_H_
