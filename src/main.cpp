#include <Geode/Geode.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include "BatchHandler.h"

using namespace geode::prelude;

class $modify(MyEffectGameObject, EffectGameObject) {

	void customSetup() {
		EffectGameObject::customSetup();
		switch(m_objectID){

			case 29: {
				setIcon("edit_eTintBGBtn_001.png"_spr);
				break;
			}
			case 30: {
				setIcon("edit_eTintGBtn_001.png"_spr);
				break;
			}
			case 105: {
				setIcon("edit_eTintObjBtn_001.png"_spr);
				break;
			}
			case 744: {
				setIcon("edit_eTint3DLBtn_001.png"_spr);
				break;
			}
			case 900: {
				setIcon("edit_eTintG2Btn_001.png"_spr);
				break;
			}
			case 915: {
				setIcon("edit_eTintLBtn_001.png"_spr);
				break;
			}
		}
	}

	void setIcon(std::string texture){
		
		if (CCSprite* newSpr = CCSprite::create(texture.c_str())) {

			setTexture(newSpr->getTexture());
			setTextureRect(newSpr->getTextureRect());
		}
	}
};

#define DO_FAKE(method) if (!BatchHandler::get()->isFake(this)) CCSpriteBatchNode::method; else CCNode::method;

class $modify(MyCCSpriteBatchNode, CCSpriteBatchNode) {

	struct Fields {
		CCSpriteBatchNode* m_self;
		~Fields() {
            BatchHandler::get()->m_batchNodes.erase(m_self);
        }
	};

	static CCSpriteBatchNode* createWithTexture(CCTexture2D* tex, unsigned int capacity) {
        auto ret = CCSpriteBatchNode::createWithTexture(tex, capacity);
		static_cast<MyCCSpriteBatchNode*>(ret)->m_fields->m_self = ret;
		BatchHandler::get()->m_batchNodes[ret] = false;
		return ret;
    }

	void setFake(bool fake) {
		BatchHandler::get()->m_batchNodes[this] = true;
	}

	bool isFake() {
		return BatchHandler::get()->isFake(this);
	}

	void draw() {
		DO_FAKE(draw());
	}

    void reorderChild(CCNode* child, int zOrder) {
		DO_FAKE(reorderChild(child, zOrder));
	}
        
    void removeChild(CCNode* child, bool cleanup) {
		DO_FAKE(removeChild(child, cleanup));
	}
	
    void removeAllChildrenWithCleanup(bool cleanup) {
		DO_FAKE(removeAllChildrenWithCleanup(cleanup));
	}

	void sortAllChildren() {
		DO_FAKE(sortAllChildren());
	}

	void visit() {
		DO_FAKE(visit());
	}

	void recursiveBlend(CCNode* node, ccBlendFunc blendFunc) {
		if (node) {
			if (CCBlendProtocol* blendNode = typeinfo_cast<CCBlendProtocol*>(node)) {
				blendNode->setBlendFunc(blendFunc);
			}
			for (CCNode* child : CCArrayExt<CCNode*>(node->getChildren())){
				if (CCBlendProtocol* blendNode = typeinfo_cast<CCBlendProtocol*>(child)) {
					recursiveBlend(child, blendFunc);
				}
			}
		}
	}

	void addChild(CCNode* child, int zOrder, int tag) {
		if (BatchHandler::get()->isFake(this)) {
			if (CCBlendProtocol* blendNode = typeinfo_cast<CCBlendProtocol*>(child)) {
				recursiveBlend(child, getBlendFunc());
			}
		}
		DO_FAKE(addChild(child, zOrder, tag));
	}

    void setBlendFunc(ccBlendFunc blendFunc) {
		CCSpriteBatchNode::setBlendFunc(blendFunc);
		if (BatchHandler::get()->isFake(this)) {
			for (CCNode* child : CCArrayExt<CCNode*>(getChildren())){
				if (CCBlendProtocol* blendNode = typeinfo_cast<CCBlendProtocol*>(child)) {
					recursiveBlend(child, blendFunc);
				}
			}
		}
	}
};

class $modify(MyCCSprite, CCSprite) {

	void setBatchNode(CCSpriteBatchNode *pobSpriteBatchNode) {
		if (pobSpriteBatchNode) {
			MyCCSpriteBatchNode* spn = static_cast<MyCCSpriteBatchNode*>(pobSpriteBatchNode);
			if (spn->isFake()) {
				pobSpriteBatchNode = nullptr;
			}
		}
		
		CCSprite::setBatchNode(pobSpriteBatchNode);
	}
};


class $modify(LevelEditorLayer) {

    bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) return false;

		for (CCSpriteBatchNode* node : CCArrayExt<CCSpriteBatchNode*>(m_batchNodes)) {
			static_cast<MyCCSpriteBatchNode*>(node)->setFake(true);
		}

		return true;
	}
};