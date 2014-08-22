/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MainScene.h"
#include "ProfileScreen.h"

USING_NS_CC;

/**
 * This is the welcome scene.
 * In this file you can find example calls to the store's interfaces.
 **/

#define SEL_GROUP "soomlaCallback"

float applyScaleForNode(cocos2d::CCNode* node) {
    cocos2d::CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scale = std::min(winSize.width / node->getContentSize().width,
                           winSize.height / node->getContentSize().height);
    node->setScale(scale);
    node->setPosition(ccp((winSize.width - node->getContentSize().width * scale) / 2,
                          (winSize.height - node->getContentSize().height * scale) / 2));
    
    return scale;
}

void fill(cocos2d::CCNode* targetNode) {
    CCPoint leftBottom =
    targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
    CCPoint rightTop =
    targetNode->getParent()->convertToWorldSpace(
                                                 ccpAdd(targetNode->getPosition(), ccpFromSize(targetNode->getContentSize())));
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float scaleX = winSize.width / (rightTop.x - leftBottom.x);
    float scaleY = winSize.height / (rightTop.y - leftBottom.y);
    
    targetNode->setScale(MAX(scaleX, scaleY));
}

CCScene* MainScene::getMainScene() {
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::sharedNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLoader::loader());

    CCBReader *ccbReader = new CCBReader(ccNodeLoaderLibrary);

    return ccbReader->createSceneWithNodeGraphFromFile("ccb/MainScreen.ccbi");
}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(CCObject *pTarget, char const *pSelectorName) {
    return NULL;
}

cocos2d::extension::Control::Handler MainScene::onResolveCCBCCControlSelector(CCObject *pTarget, char const *pSelectorName) {
    return NULL;
}

bool MainScene::onAssignCCBMemberVariable(CCObject *pTarget, char const *pMemberVariableName, CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackgroundNode", CCNode*, mBackgroundNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainNode", CCNode*, mMainNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUnlockArea", CCNode*, mUnlockArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUnlocker", CCNode*, mUnlocker);
    return false;
}

void MainScene::onNodeLoaded(CCNode *pNode, NodeLoader *pNodeLoader) {
    CC_ASSERT(mBackgroundNode);
    CC_ASSERT(mMainNode);
    CC_ASSERT(mUnlockArea);
    CC_ASSERT(mUnlocker);

    applyScaleForNode(this);
    fill(mBackgroundNode);

    this->setKeypadEnabled(true);
}

void MainScene::onEnter() {
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](CCTouch* touch, CCEvent* event) {
        this->mOriginalPos = this->mUnlocker->getPosition();
        return true;
    };
    listener->onTouchMoved = [this](CCTouch* touch, CCEvent* event) {
        CCPoint touchPoint = touch->getLocation();
        this->mUnlocker->setPosition(this->mUnlocker->getParent()->convertToNodeSpace(touchPoint));
    };
    listener->onTouchEnded = [this](CCTouch* touch, CCEvent* event) {
        CCRect rect1 = this->mUnlocker->boundingBox();
        CCRect rect2 = this->mUnlockArea->boundingBox();

        if (rect1.intersectsRect(rect2)) {
            CCScene *s = ProfileScreen::createScene();
            CCDirector::sharedDirector()->setDepthTest(true);
            CCTransitionScene *transition = CCTransitionMoveInR::create(0.8f, s);

            CCDirector::sharedDirector()->replaceScene(transition);
        }
        else {
            // Snap
            this->mUnlocker->runAction(CCMoveTo::create(0.2f, this->mOriginalPos));
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    CCLayer::onEnter();
}

void MainScene::onExit() {
    _eventDispatcher->removeEventListener(listener);

    CCLayer::onExit();
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    Layer::onKeyReleased(keyCode, event);
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
        CCDirector::sharedDirector()->end();
    }
}