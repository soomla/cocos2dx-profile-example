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

#ifndef __ProfileEventHandler_H_
#define __ProfileEventHandler_H_

#include "cocos2d.h"

class ProfileEventHandler : public cocos2d::CCObject {

public:
    ProfileEventHandler();
    virtual void onProfileInitialized(cocos2d::CCDictionary *eventData);
    virtual void onUserRatingEvent(cocos2d::CCDictionary *eventData);
    virtual void onLoginFinished(cocos2d::CCDictionary *eventData);
    virtual void onLoginStarted(cocos2d::CCDictionary *eventData);
    virtual void onLoginCancelledEvent(cocos2d::CCDictionary *eventData);
    virtual void onLoginFailed(cocos2d::CCDictionary *eventData);
    
    virtual void onLogoutFailed(cocos2d::CCDictionary *eventData);
    virtual void onLogoutFinished(cocos2d::CCDictionary *eventData);
    virtual void onLogoutStarted(cocos2d::CCDictionary *eventData);
    
    virtual void onGetContactsFailed(cocos2d::CCDictionary *eventData);
    virtual void onGetContactsFinished(cocos2d::CCDictionary *eventData);
    virtual void onGetContactsStarted(cocos2d::CCDictionary *eventData);
    
    virtual void onGetFeedFailed(cocos2d::CCDictionary *eventData);
    virtual void onGetFeedFinished(cocos2d::CCDictionary *eventData);
    virtual void onGetFeedStarted(cocos2d::CCDictionary *eventData);
    
    virtual void onSocialActionFailedEvent(cocos2d::CCDictionary *eventData);
    virtual void onSocialActionFinishedEvent(cocos2d::CCDictionary *eventData);
    virtual void onSocialActionStartedEvent(cocos2d::CCDictionary *eventData);
    
    virtual void onUserProfileUpdatedEvent(cocos2d::CCDictionary *eventData);
};


#endif //__ProfileEventHandler_H_
