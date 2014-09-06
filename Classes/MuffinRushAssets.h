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
// Created by Fedor Shubin on 5/24/13.
//


#ifndef __MuffinRushAssets_H_
#define __MuffinRushAssets_H_

#include "CCStoreAssets.h"
#include "cocos2d.h"

#define MUFFIN_CURRENCY_ITEM_ID "currency_muffin"
#define TENMUFF_PACK_PRODUCT_ID "android.test.refunded"
#define FIFTYMUFF_PACK_PRODUCT_ID "android.test.canceled"
#define FOURHUNDMUFF_PACK_PRODUCT_ID "android.test.purchased"
#define THOUSANDMUFF_PACK_PRODUCT_ID "android.test.item_unavailable"
#define NO_ADDS_NONCONS_PRODUCT_ID "no_ads"

#define MUFFINCAKE_ITEM_ID "fruit_cake"
#define PAVLOVA_ITEM_ID "pavlova"
#define CHOCLATECAKE_ITEM_ID "chocolate_cake"
#define CREAMCUP_ITEM_ID "cream_cup"

class MuffinRushAssets: public soomla::CCStoreAssets {
    cocos2d::CCArray *mCurrencies;
    cocos2d::CCArray *mGoods;
    cocos2d::CCArray *mCurrencyPacks;
    cocos2d::CCArray *mCategories;
    cocos2d::CCArray *mNonConsumableItems;
public:
    MuffinRushAssets():
    mCurrencies(NULL),
    mGoods(NULL),
    mCurrencyPacks(NULL),
    mCategories(NULL),
    mNonConsumableItems(NULL)
    {}

    virtual ~MuffinRushAssets();

    static MuffinRushAssets *create();
    bool init();

    virtual int getVersion();

    virtual cocos2d::CCArray *getCurrencies();

    virtual cocos2d::CCArray *getGoods();

    virtual cocos2d::CCArray *getCurrencyPacks();

    virtual cocos2d::CCArray *getCategories();

    virtual cocos2d::CCArray *getNonConsumableItems();
};


#endif //__MuffinRushAssets_H_
