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

#include "CoreEventHandler.h"
#include "Cocos2dxCore.h"

#define TAG "CoreEventHandler >>>"

USING_NS_CC;
using namespace soomla;

CoreEventHandler::CoreEventHandler() {
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CoreEventHandler::onRewardGivenEvent), CCCoreConsts::EVENT_REWARD_GIVEN, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CoreEventHandler::onRewardTakenEvent), CCCoreConsts::EVENT_REWARD_TAKEN, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CoreEventHandler::onCustomEvent), CCCoreConsts::EVENT_CUSTOM, NULL);
}

void CoreEventHandler::onRewardGivenEvent(cocos2d::CCDictionary *eventData) {
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Reward %s was given", reward->getName()->getCString())->getCString());
}

void CoreEventHandler::onRewardTakenEvent(cocos2d::CCDictionary *eventData) {
    CCReward *reward = dynamic_cast<CCReward *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Reward %s was taken", reward->getName()->getCString())->getCString());
}

void CoreEventHandler::onCustomEvent(cocos2d::CCDictionary *eventData) {
    CCString *name = dynamic_cast<CCString *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_NAME));
//    CCDictionary *extra = dynamic_cast<CCDictionary *>(eventData->objectForKey(CCCoreConsts::DICT_ELEMENT_EXTRA));
    CCSoomlaUtils::logDebug(TAG, CCString::createWithFormat("Custom event arrived %s", name->getCString())->getCString());
}