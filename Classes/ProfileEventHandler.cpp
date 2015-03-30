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
#include "Cocos2dxProfile.h"

#define TAG "ProfileEventHandler >>>"

USING_NS_CC;
using namespace soomla;

ProfileEventHandler::ProfileEventHandler() {
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onProfileInitialized), CCProfileConsts::EVENT_PROFILE_INITIALIZED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onUserRatingEvent), CCProfileConsts::EVENT_USER_RATING, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLoginFailed), CCProfileConsts::EVENT_LOGIN_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLoginFinished), CCProfileConsts::EVENT_LOGIN_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLoginStarted), CCProfileConsts::EVENT_LOGIN_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLoginCancelledEvent), CCProfileConsts::EVENT_LOGIN_CANCELLED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLogoutFailed), CCProfileConsts::EVENT_LOGOUT_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLogoutFinished), CCProfileConsts::EVENT_LOGOUT_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onLogoutStarted), CCProfileConsts::EVENT_LOGOUT_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetContactsFailed), CCProfileConsts::EVENT_GET_CONTACTS_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetContactsFinished), CCProfileConsts::EVENT_GET_CONTACTS_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetContactsStarted), CCProfileConsts::EVENT_GET_CONTACTS_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetFeedFailed), CCProfileConsts::EVENT_GET_FEED_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetFeedFinished), CCProfileConsts::EVENT_GET_FEED_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onGetFeedStarted), CCProfileConsts::EVENT_GET_FEED_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onSocialActionFailedEvent), CCProfileConsts::EVENT_SOCIAL_ACTION_FAILED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onSocialActionFinishedEvent), CCProfileConsts::EVENT_SOCIAL_ACTION_FINISHED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onSocialActionStartedEvent), CCProfileConsts::EVENT_SOCIAL_ACTION_STARTED, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ProfileEventHandler::onUserProfileUpdatedEvent), CCProfileConsts::EVENT_USER_PROFILE_UPDATED, NULL);
}

void ProfileEventHandler::onProfileInitialized(cocos2d::CCDictionary *eventData) {
    CCSoomlaUtils::logDebug(TAG, "Profile has initialized");
}

void ProfileEventHandler::onUserRatingEvent(cocos2d::CCDictionary *eventData) {
    CCSoomlaUtils::logDebug(TAG, "Market rating page has opened");
}

void ProfileEventHandler::onLoginFailed(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *errorDescription = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Login to %s has failed: %s (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginFinished(cocos2d::CCDictionary *eventData) {
    CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_USER_PROFILE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("onLoginFinished %s (%s)", userProfile->getProvider()->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginStarted(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Login to %s has started (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLoginCancelledEvent(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Login to %s has cancelled (%s)", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onLogoutFailed(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *errorDescription = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Login to %s has FAILED: %s", soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString())->getCString());
}

void ProfileEventHandler::onLogoutFinished(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Logout from %s has finished",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString())->getCString());
}

void ProfileEventHandler::onLogoutStarted(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Logout from %s has started",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString())->getCString());
}

void ProfileEventHandler::onGetContactsFailed(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *errorDescription = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get contacts from %s has FAILED: %s (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onGetContactsFinished(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    CCArray *contactsArray = dynamic_cast<CCArray *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_CONTACTS));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get contacts from %s has finished (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
    
    for (int i = 0; i < contactsArray->count(); ++i){
        soomla::CCUserProfile * contact = dynamic_cast<soomla::CCUserProfile *>(contactsArray->objectAtIndex(i));
        
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("CONTACT %s %s",
                                                                contact->getFirstName()->getCString(),
                                                                contact->getLastName()->getCString())->getCString());
    }
}

void ProfileEventHandler::onGetContactsStarted(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get contacts from %s has started (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onGetFeedFailed(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *errorDescription = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get feed from %s has FAILED: %s (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onGetFeedFinished(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    CCArray *feedList = dynamic_cast<CCArray *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_FEEDS));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get feed from %s has finished (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
    
    for (int i = 0; i < feedList->count(); ++i){
        CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("FEED %s",
                                                                (dynamic_cast<CCString *>(feedList->objectAtIndex(i))->getCString()))->getCString());
    }
}

void ProfileEventHandler::onGetFeedStarted(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Get feed from %s has started (%s)",
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionFailedEvent(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    CCString *errorDescription = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_MESSAGE));
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Social action %s on %s has FAILED: %s (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            errorDescription->getCString(), payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionFinishedEvent(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Social action %s on %s has finished (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onSocialActionStartedEvent(cocos2d::CCDictionary *eventData) {
    CCProvider provider = CCProvider((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PROVIDER)))->getValue());
    CCSocialActionType socialActionType = CCSocialActionType((dynamic_cast<CCInteger *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_SOCIAL_ACTION_TYPE)))->getValue());
    CCString *payload = dynamic_cast<CCString *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_PAYLOAD));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Social action %s on %s has started (%s)",
                                                            soomla::CCSocialActionUtils::actionEnumToString(socialActionType)->getCString(),
                                                            soomla::CCUserProfileUtils::providerEnumToString(provider)->getCString(),
                                                            payload->getCString())->getCString());
}

void ProfileEventHandler::onUserProfileUpdatedEvent(cocos2d::CCDictionary *eventData) {
    CCUserProfile *userProfile = dynamic_cast<CCUserProfile *>(eventData->objectForKey(CCProfileConsts::DICT_ELEMENT_USER_PROFILE));
    
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("onUserProfileUpdatedEvent %s",
                                                            userProfile->getProvider()->getCString())->getCString());
}
