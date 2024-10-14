#include <Geode/Geode.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/CCSprite.hpp>

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
			m_hasSpecialChild = true;
			setTexture(newSpr->getTexture());
			setTextureRect(newSpr->getTextureRect());
		}
	}
};