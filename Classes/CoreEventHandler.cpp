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

#define TAG "CoreEventHandler >>>"

USING_NS_CC;

void CoreEventHandler::onRewardGivenEvent(soomla::CCReward *reward) {
    CCLOG("%s Reward %s was given", TAG, reward->getName()->getCString());
}

void CoreEventHandler::onRewardTakenEvent(soomla::CCReward *reward) {
    CCLOG("%s Reward %s was taken", TAG, reward->getName()->getCString());
}

void CoreEventHandler::onCustomEvent(cocos2d::CCString *name, cocos2d::CCDictionary *extra) {
    CCLOG("%s Custom event received %s", TAG, name->getCString());
}