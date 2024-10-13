#pragma once

#include <Geode/Geode.hpp>

class BatchHandler {

//this exists to efficiently add fields without to much of a performance impact

protected:
    static BatchHandler* instance;
public:
    std::unordered_map<cocos2d::CCSpriteBatchNode*, bool> m_batchNodes;

    static BatchHandler* get(){

        if (!instance) {
            instance = new BatchHandler();
        };
        return instance;
    }

    bool isFake(cocos2d::CCSpriteBatchNode* node);
};
