//
// Created by Fedor Shubin on 5/24/13.
//


#ifndef __MuffinRushAssets_H_
#define __MuffinRushAssets_H_

#include "CCStoreAssets.h"
#include "cocos2d.h"

class MuffinRushAssets: public soomla::CCStoreAssets {
    cocos2d::Array *mCurrencies;
    cocos2d::Array *mGoods;
    cocos2d::Array *mCurrencyPacks;
    cocos2d::Array *mCategories;
public:
    MuffinRushAssets():
    mCurrencies(NULL),
    mGoods(NULL),
    mCurrencyPacks(NULL),
    mCategories(NULL)
    {}

    virtual ~MuffinRushAssets();

    static MuffinRushAssets *create();
    bool init();

    virtual int getVersion();

    virtual cocos2d::CCArray *getCurrencies();

    virtual cocos2d::CCArray *getGoods();

    virtual cocos2d::CCArray *getCurrencyPacks();

    virtual cocos2d::CCArray *getCategories();
};


#endif //__MuffinRushAssets_H_
