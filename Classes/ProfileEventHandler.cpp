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

#include "ProfileEventHandler.h"

#define TAG "ProfileEventHandler >>>"

USING_NS_CC;

void ProfileEventHandler::onProfileInitialized() {
    CCLOG("%s Profile module has initialized", TAG);
}

void ProfileEventHandler::onUserRatingEvent() {
    CCLOG("%s Market rating page has opened", TAG);
}

void ProfileEventHandler::onLoginFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) {
    CCLOG("%s Login to %s has failed: %s (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), errorDescription->getCString(),
        payload->getCString());
}

void ProfileEventHandler::onLoginFinished(soomla::CCUserProfile *userProfile, cocos2d::CCString *payload) {
    CCLOG("%s %s (%s)", TAG, "onLoginFinished", payload->getCString());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(soomla::CCProfileConsts::EVENT_LOGIN_FINISHED,
                                                                       userProfile);
}

void ProfileEventHandler::onLoginStarted(soomla::CCProvider provider, cocos2d::CCString *payload) {
    CCLOG("%s Login to %s has started (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
}

void ProfileEventHandler::onLoginCancelledEvent(soomla::CCProvider provider, cocos2d::CCString *payload) {
    CCLOG("%s Login to %s has cancelled (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
}

void ProfileEventHandler::onLogoutFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription) {
    CCLOG("%s Login to %s has FAILED: %s", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), errorDescription->getCString());
}

void ProfileEventHandler::onLogoutFinished(soomla::CCProvider provider) {
    CCLOG("%s Logout from %s has finished", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(soomla::CCProfileConsts::EVENT_LOGOUT_FINISHED);
}

void ProfileEventHandler::onLogoutStarted(soomla::CCProvider provider) {
    CCLOG("%s Logout from %s has started", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString());
}

void ProfileEventHandler::onGetContactsFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) {
    CCLOG("%s Get contacts from %s has FAILED: %s (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        errorDescription->getCString(), payload->getCString());
}

void ProfileEventHandler::onGetContactsFinished(soomla::CCProvider provider, cocos2d::CCArray *contactsDict, cocos2d::CCString *payload) {
    CCLOG("%s Get contacts from %s has finished (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
    
    for (int i = 0; i < contactsDict->count(); ++i){
        soomla::CCUserProfile * contact = dynamic_cast<soomla::CCUserProfile *>(contactsDict->objectAtIndex(i));
        
        CCLOG("%s CONTACT %s %s", TAG, contact->getFirstName()->getCString(), contact->getLastName()->getCString());
    }
}

void ProfileEventHandler::onGetContactsStarted(soomla::CCProvider provider, cocos2d::CCString *payload) {
    CCLOG("%s Get contacts from %s has started (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
}

void ProfileEventHandler::onGetFeedFailed(soomla::CCProvider provider, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) {
    CCLOG("%s Get feed from %s has FAILED: %s (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
         errorDescription->getCString(), payload->getCString());
}

void ProfileEventHandler::onGetFeedFinished(soomla::CCProvider provider, cocos2d::CCArray *feedList, cocos2d::CCString *payload) {
    CCLOG("%s Get feed from %s has finished (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
    
    for (int i = 0; i < feedList->count(); ++i){
        CCLOG("%s FEED %s", TAG, (dynamic_cast<CCString *>(feedList->objectAtIndex(i))->getCString()));
    }
}

void ProfileEventHandler::onGetFeedStarted(soomla::CCProvider provider, cocos2d::CCString *payload) {
    CCLOG("%s Get feed from %s has started (%s)", TAG, soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        payload->getCString());
}

void ProfileEventHandler::onSocialActionFailedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::CCString *errorDescription, cocos2d::CCString *payload) {
    CCLOG("%s Social action %s on %s has FAILED: %s (%s)", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
        errorDescription->getCString(), payload->getCString());
}

void ProfileEventHandler::onSocialActionFinishedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::CCString *payload) {
    CCLOG("%s Social action %s on %s has finished (%s)", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), payload->getCString());
}

void ProfileEventHandler::onSocialActionStartedEvent(soomla::CCProvider provider, soomla::CCSocialActionType socialActionType, cocos2d::CCString *payload) {
    CCLOG("%s Social action %s on %s has started (%s)", TAG, soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
        soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(), payload->getCString());
}

void ProfileEventHandler::onUserProfileUpdatedEvent(soomla::CCUserProfile *userProfile) {
    CCLOG("%s %s", TAG, "onUserProfileUpdatedEvent");
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(soomla::CCProfileConsts::EVENT_USER_PROFILE_UPDATED,
                                                                       userProfile);
}
