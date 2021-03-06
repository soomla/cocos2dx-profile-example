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
#include "MuffinRushAssets.h"
#include "ProfileEventHandler.h"
#include "CoreEventHandler.h"
#include "Cocos2dxProfile.h"
#include "Cocos2dxStore.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    handler = new ProfileEventHandler();
    coreHandler = new CoreEventHandler();
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    soomla::CCSoomla::initialize("customSecret");
    
    MuffinRushAssets *assets = MuffinRushAssets::create();
    
    __Dictionary *storeParams = __Dictionary::create();
    storeParams->setObject(__String::create("ExamplePublicKey"), "androidPublicKey");
    
    soomla::CCSoomlaStore::initialize(assets, storeParams);
    
    __Dictionary *profileParams = __Dictionary::create();
    __Dictionary *twitterParams = __Dictionary::create();
    twitterParams->setObject(__String::create("T8NMGwKq6USYCjZox86Bxd2RJ"), "consumerKey");
    twitterParams->setObject(__String::create("TO88J9QjIJlSGfuyfza9Ox2OgTsLc1rjcmaJknlIMuUw0T1I30"), "consumerSecret");
    
    profileParams->setObject(twitterParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::TWITTER)->getCString());
    
    __Dictionary *googleParams = __Dictionary::create();
    googleParams->setObject(__String::create("833688084302-sg4q1vug2ivehp54lu86rig3p0b0q85v.apps.googleusercontent.com"), "clientId");
    
    profileParams->setObject(googleParams, soomla::CCUserProfileUtils::providerEnumToString(soomla::GOOGLE)->getCString());
    
    soomla::CCSoomlaProfile::initialize(profileParams);
    
    // initialize director
    auto director = Director::getInstance();
    
    auto glview = director->getOpenGLView();
    if(!glview) {
#if COCOS2D_VERSION > 0x00030200
        glview = GLViewImpl::create("My Game");
#else
        glview = GLView::create("My Game");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = ProfileScreen::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
