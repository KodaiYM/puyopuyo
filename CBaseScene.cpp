#include "CBaseScene.h"
#include <stdio.h>

CBaseScene::CBaseScene(ISceneChanger* changer) {
	mSceneChanger = changer;
}
