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
// Created by Fedor Shubin on 6/14/14.
//


#include "CCProfileEventHandler.h"

#ifndef __ProfileEventHandler_H_
#define __ProfileEventHandler_H_


class ProfileEventHandler: public soomla::CCProfileEventHandler {

public:
    virtual void onProfileInitialized();
    virtual void onUserRatingEvent();
    virtual void onLoginFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription);
    virtual void onLoginFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);
    virtual void onLoginFinished(soomla::CCUserProfile *userProfile, cocos2d::__String *payload);
    virtual void onLoginStarted(soomla::CCProvider provider, cocos2d::__String *payload);
    virtual void onLoginCancelledEvent(soomla::CCProvider provider, cocos2d::__String *payload);
    
    virtual void onLogoutFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription);
    virtual void onLogoutFinished(soomla::CCProvider provider);
    virtual void onLogoutStarted(soomla::CCProvider provider);
    
    virtual void onGetContactsFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);
    virtual void onGetContactsFinished(soomla::CCProvider provider, cocos2d::__Array *contactsDict, cocos2d::__String *payload);
    virtual void onGetContactsStarted(soomla::CCProvider provider, cocos2d::__String *payload);
    
    virtual void onGetFeedFailed(soomla::CCProvider provider, cocos2d::__String *errorDescription, cocos2d::__String *payload);
    virtual void onGetFeedFinished(soomla::CCProvider provider, cocos2d::__Array *feedList, cocos2d::__String *payload);
    virtual void onGetFeedStarted(soomla::CCProvider provider, cocos2d::__String *payload);
    
    virtual void onSocialActionFailedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::__String *errorDescription, cocos2d::__String *payload);
    virtual void onSocialActionFinishedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::__String *payload);
    virtual void onSocialActionStartedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::__String *payload);
    
    virtual void onUserProfileUpdatedEvent(soomla::CCUserProfile *userProfile);
};


#endif //__ProfileEventHandler_H_
