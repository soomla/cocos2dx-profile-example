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

#include "AppDelegate.h"
#include "ProfileScreen.h"
#include "CoreEventHandler.h"
#include "ProfileEventHandler.h"
#include "MuffinRushAssets.h"
#include "Cocos2dxStore.h"
#include "Cocos2dxProfile.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    handler = new ProfileEventHandler();
    coreHandler = new CoreEventHandler();
}

AppDelegate::~AppDelegate() 
{
    soomla::CCProfileEventDispatcher::getInstance()->removeEventHandler(handler);
    soomla::CCCoreEventDispatcher::getInstance()->removeEventHandler(coreHandler);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    soomla::CCSoomla::initialize("customSecret");
    
    MuffinRushAssets *assets = MuffinRushAssets::create();
    
    CCDictionary *storeParams = CCDictionary::create();
    storeParams->setObject(CCString::create("ExamplePublicKey"), "androidPublicKey");
    storeParams->setObject(CCBool::create(true), "testPurchases");
    
    soomla::CCCoreEventDispatcher::getInstance()->addEventHandler(coreHandler);
    soomla::CCSoomlaStore::initialize(assets, storeParams);
    
    CCDictionary *profileParams = CCDictionary::create();
    
    CCDictionary *twitterParams = CCDictionary::create();
    twitterParams->setObject(CCString::create("T8NMGwKq6USYCjZox86Bxd2RJ"), "consumerKey");
    twitterParams->setObject(CCString::create("TO88J9QjIJlSGfuyfza9Ox2OgTsLc1rjcmaJknlIMuUw0T1I30"), "consumerSecret");
    
    profileParams->setObject(twitterParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::TWITTER)->getCString());
    
    CCDictionary *googleParams = CCDictionary::create();
    googleParams->setObject(CCString::create("833688084302-8u16egrn1jiobqgoi8s64ul9qaj3tjrn.apps.googleusercontent.com"), "clientId");
    
    profileParams->setObject(googleParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::GOOGLE)->getCString());
    
    soomla::CCProfileEventDispatcher::getInstance()->addEventHandler(handler);
    soomla::CCSoomlaProfile::initialize(profileParams);
    
    // initialize director
    CCDirector *director = CCDirector::sharedDirector();
    
    CCDirector::sharedDirector()->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *scene = ProfileScreen::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
