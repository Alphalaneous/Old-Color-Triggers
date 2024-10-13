
#include <Geode/Geode.hpp>
#include "BatchHandler.h"

BatchHandler* BatchHandler::instance = nullptr;

bool BatchHandler::isFake(cocos2d::CCSpriteBatchNode* node) {
    return m_batchNodes[node];
}
